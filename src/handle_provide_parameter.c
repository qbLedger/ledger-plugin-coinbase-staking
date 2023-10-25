#include "kiln_plugin.h"

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

        default:
            PRINTF("Selector Index not supported: %d\n", context->selectorIndex);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}
