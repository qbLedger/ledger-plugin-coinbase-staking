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
    * otherwise set it to "UNKNOWN"
    *
    * @param address: address to check
    * @param context: context to update
    * 
    * @note impacts the following context storage:
    *   `context->lr_erc20_name`: name of the erc20
*/
void find_lr_known_erc20(const char *address, context_t *context) {
    for (size_t i = 0; i < LR_STRATEGIES_COUNT; i++) {
        if (compare_addresses(address, &lr_erc20_addresses[i])) {
            strncpy(context->lr_erc20_name, &lr_tickers[i], MAX_TICKER_LEN); 
            return;  
        }
    }
    // if unknown erc20, indicate it
    strncpy(context->lr_erc20_name, "UNKNOWN", MAX_TICKER_LEN);
}

/*
    * If address is a known strategy, update lr display context with its name
    * otherwise set it to "UNKNOWN"
    * 
    * @param address: address to check
    * @param context: context to update
    * 
    *  @note impacts the following context storage:
    *   `context->lr_strategy_name`: name of the strategy
*/
void find_lr_known_strategy(const char *address, context_t *context) {
    for (size_t i = 0; i < LR_STRATEGIES_COUNT; i++) {
        if (compare_addresses(address, &lr_strategy_addresses[i])) {
            strncpy(context->lr_strategy_name, &lr_tickers[i], MAX_TICKER_LEN); 
            return;  
        }
    }
    // if unknown strategy, indicate it
    strncpy(context->lr_strategy_name, "UNKNOWN", MAX_TICKER_LEN);
}

/*
    * Handle the parameters for the depositIntoStrategy(strategy,erc20,amount)
    * selector
    * 
    * @param msg: message containing the parameter
    * @param context: context to update
    * 
    * @note impacts the following context storage:
    *   `context->lr_strategy_address`: address of the strategy
    *   `context->lr_strategy_name`: name of the strategy
    *   `context->lr_erc20_address`: address of the erc20
    *   `context->lr_erc20_name`: name of the erc20
    *   `context->lr_erc20_amount`: amount of the erc20
*/
void handle_lr_deposit_into_strategy(ethPluginProvideParameter_t *msg, context_t *context) {
    uint8_t buffer[ADDRESS_LENGTH];
    
    switch (context->next_param) {
        case LR_DEPOSIT_INTO_STRATEGY_STRATEGY:
            copy_address(
                buffer,
                msg->parameter,
                sizeof(buffer)
            );
            getEthDisplayableAddress(
                buffer,
                context->lr_strategy_address,
                sizeof(context->lr_strategy_address),
                msg->pluginSharedRW->sha3,
                0
            );
            find_lr_known_strategy(context->lr_strategy_address, context);

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
                context->lr_erc20_address,
                sizeof(context->lr_erc20_address),
                msg->pluginSharedRW->sha3,
                0
            );
            find_lr_known_erc20(context->lr_erc20_address, context);

            context->next_param = LR_DEPOSIT_INTO_STRATEGY_AMOUNT;
            break;
        case LR_DEPOSIT_INTO_STRATEGY_AMOUNT:
            copy_parameter(
                context->lr_erc20_amount,
                msg->parameter,
                sizeof(context->lr_erc20_amount)
            );
            context->next_param = LR_DEPOSIT_INTO_STRATEGY_UNEXPECTED_PARAMETER;
            break;
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
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
