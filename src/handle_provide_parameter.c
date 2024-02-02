#include "kiln_plugin.h"

/* 
    * Compare two addresses
    *
    * @param a: first address
    * @param b: second address
    * 
    * @return true if the addresses are the same
*/
bool compare_addresses(const char *a, const char *b) {
    for (size_t i = 0; i < ADDRESS_STR_LEN; i += 1) {
        if (tolower((unsigned char)a[i]) != tolower((unsigned char)b[i])) {
            return false;
        }
    }
    return true;
}

/*
    * If address is a known erc20, update lr display context with its name
    * otherwise set it to unkwown (-1)
    *
    * @param address: address to compare
    * @param index: index of the erc20 in the context
    * @param context: context to update
    * 
    * @note impacts the following context storage:
    * `context->lr_strategy_to_display`: set index of the erc20 in the context
*/
void find_lr_known_erc20(const char *address, size_t index, context_t *context) {
    for (size_t i = 0; i < LR_STRATEGIES_COUNT; i++) {
        if (compare_addresses(address, &lr_erc20_addresses[i])) {
            context->lr_erc20_to_display[index] = i;
            return;  
        }
    }
    // if unknown erc20, indicate it
    context->lr_erc20_to_display[index] = -1;
}

/*
    * If address is a known strategy, update lr display context with its name
    * otherwise set it to unkwown (-1)
    * 
    * @param address: address to compare
    * @param index: index of the strategy in the context
    * @param context: context to update
    * 
    * @note impacts the following context storage:
    *  `context->lr_strategy_to_display`: set index of the strategy in the context
*/
void find_lr_known_strategy(const char *address, size_t index, context_t *context) {
    for (size_t i = 0; i < LR_STRATEGIES_COUNT; i++) {
        if (compare_addresses(address, &lr_strategy_addresses[i])) {
            context->lr_strategy_to_display[index] = i;
            return;  
        }
    }
    // if unknown strategy, indicate it
    context->lr_strategy_to_display[index] = -1;
}

/*
    * Handle the parameters for the depositIntoStrategy(strategy,erc20,amount)
    * selector
    * 
    * @param msg: message containing the parameter
    * @param context: context to update
    * 
    * @note impacts the following context storage:
    *   `context->next_param`: set to the next parameter to handle    
    *   `context->lr_strategy_to_display`: set index of the strategy in the context
    *   `context->lr_erc20_to_display`: set index of the erc20 in the context
    *   `context->lr_erc20_amount_to_display`: set amount of the erc20 in the context
    *
*/
void handle_lr_deposit_into_strategy(ethPluginProvideParameter_t *msg, context_t *context) {
    uint8_t buffer[ADDRESS_LENGTH];
    char address_buffer[ADDRESS_STR_LEN];
    
    switch (context->next_param) {
        case LR_DEPOSIT_INTO_STRATEGY_STRATEGY:
            copy_address(
                buffer,
                msg->parameter,
                sizeof(buffer)
            );
            getEthDisplayableAddress(
                buffer,
                address_buffer,
                sizeof(address_buffer),
                msg->pluginSharedRW->sha3,
                0
            );
            find_lr_known_strategy(&address_buffer, 0, context);

            context->next_param = LR_DEPOSIT_INTO_STRATEGY_TOKEN;
            break;
        case LR_DEPOSIT_INTO_STRATEGY_TOKEN:
            copy_address(
                buffer,
                msg->parameter,
                sizeof(buffer)
            );
            getEthDisplayableAddress(
                buffer,
                address_buffer,
                sizeof(address_buffer),
                msg->pluginSharedRW->sha3,
                0
            );
            find_lr_known_erc20(&address_buffer, 0, context);

            context->next_param = LR_DEPOSIT_INTO_STRATEGY_AMOUNT;
            break;
        case LR_DEPOSIT_INTO_STRATEGY_AMOUNT:
            copy_parameter(
                context->lr_erc20_amount_to_display[0],
                msg->parameter,
                sizeof(context->lr_erc20_amount_to_display[0])
            );
            context->next_param = LR_DEPOSIT_INTO_STRATEGY_UNEXPECTED_PARAMETER;
            break;
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

void handle_lr_queue_withdrawal(ethPluginProvideParameter_t *msg, context_t *context) {
    switch (context->next_param) {
        case LR_QUEUE_WITHDRAWAL_STRATEGY_INDEXES_OFFSET:
            context->next_param = LR_QUEUE_WITHDRAWAL_STRATEGIES_OFFSET;
            break;
        case LR_QUEUE_WITHDRAWAL_STRATEGIES_OFFSET:
            context->next_param = LR_QUEUE_WITHDRAWAL_SHARES_OFFSET;
            break;
        case LR_QUEUE_WITHDRAWAL_SHARES_OFFSET:
            context->next_param = LR_QUEUE_WITHDRAWAL_WITHDRAWER;
            break;
        case LR_QUEUE_WITHDRAWAL_WITHDRAWER:
            context->next_param = LR_QUEUE_WITHDRAWAL_UNDELEGATEIFPOSSIBLE;
            break;
        case LR_QUEUE_WITHDRAWAL_UNDELEGATEIFPOSSIBLE:
            context->next_param = LR_QUEUE_WITHDRAWAL_UNEXPECTED_PARAMETER;
            break;
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            //msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

void handle_provide_parameter(ethPluginProvideParameter_t *msg) {
    context_t *context = (context_t *) msg->pluginContext;

    PRINTF("plugin provide parameter: offset %d\nBytes: %.*H\n",
           msg->parameterOffset,
           PARAMETER_LENGTH,
           msg->parameter);

    switch (context->selectorIndex) {
        case KILN_V1_DEPOSIT:
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;

        case KILN_V1_WITHDRAW:
        case KILN_V1_WITHDRAW_EL:
        case KILN_V1_WITHDRAW_CL:
            msg->result = ETH_PLUGIN_RESULT_OK;
            break;
        case KILN_V1_BATCH_WITHDRAW:
        case KILN_V1_BATCH_WITHDRAW_EL:
        case KILN_V1_BATCH_WITHDRAW_CL:
            msg->result = ETH_PLUGIN_RESULT_OK;
            break;

        case KILN_V1_REQUEST_EXIT:
            msg->result = ETH_PLUGIN_RESULT_OK;
            break;

        case KILN_V2_STAKE:
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
        case KILN_V2_REQUEST_EXIT:
        case KILN_V2_MULTICLAIM:
        case KILN_V2_CLAIM:
            msg->result = ETH_PLUGIN_RESULT_OK;
            break;

        case KILN_LR_DEPOSIT_INTO_STRATEGY:
            handle_lr_deposit_into_strategy(msg, context);
            break;
        case KILN_LR_QUEUE_WITHDRAWAL:
            handle_lr_queue_withdrawal(msg, context);
            break;
        case KILN_LR_QUEUE_WITHDRAWALS:
        case KILN_LR_COMPLETE_QUEUED_WITHDRAWAL:
            msg->result = ETH_PLUGIN_RESULT_OK;
            break;

        default:
            PRINTF("Selector Index not supported: %d\n", context->selectorIndex);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}
