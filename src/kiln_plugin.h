#pragma once

#include <string.h>

#include "eth_internals.h"
#include "eth_plugin_interface.h"

#define PLUGIN_NAME        "Kiln"
#define VALIDATOR_KEY_SIZE 48

// Available selectors:
//
// V1 selectors
// --- 0. deposit()
// --- 1. withdraw(validator_pubkey)
// --- 2. withdrawEL(validator_pubkey)
// --- 3. withdrawCL(validator_pubkey)
// --- 4. batchWithdraw(validator_pubkeys)
// --- 5. batchWithdrawEL(validator_pubkeys)
// --- 6. batchWithdrawCL(validator_pubkeys)
// --- 7. requestValidatorsExit(validator_pubkeys)
//
// V2 selectors
// --- 8. stake()
// --- 9. requestExit(shares_count)
// --- 10. multiClaim(exit_queues, ticket_ids, cask_ids)
// --- 11. claim(uint256[],uint32[],uint16)
#define NUM_SELECTORS 12

// Selectors available (see mapping above).
typedef enum {
    KILN_V1_DEPOSIT = 0,
    KILN_V1_WITHDRAW,
    KILN_V1_WITHDRAW_EL,
    KILN_V1_WITHDRAW_CL,
    KILN_V1_BATCH_WITHDRAW,
    KILN_V1_BATCH_WITHDRAW_EL,
    KILN_V1_BATCH_WITHDRAW_CL,
    KILN_V1_REQUEST_EXIT,
    KILN_V2_STAKE,
    KILN_V2_REQUEST_EXIT,
    KILN_V2_MULTICLAIM,
    KILN_V2_CLAIM,
} selector_t;

// Parameters for deposit selector.
typedef enum {
    DEPOSIT_UNEXPECTED_PARAMETER,
} deposit_parameters;

// Parameters for withdraw selectors (applies to withdraw, withdrawEL, withdrawCL)
typedef enum {
    WITHDRAW_VALIDATION_OFFSET = 0,
    WITHDRAW_VALIDATION_LENGTH = 1,
    WITHDRAW_VALIDATION_KEY_PART_1 = 2,  // BLS keys are 48 bytes, thus they are
    WITHDRAW_VALIDATION_KEY_PART_2 = 3,  // taking 2x32 bytes parameters.
    WITHDRAW_UNEXPECTED_PARAMETER,
} withdraw_parameters;

extern const uint32_t KILN_SELECTORS[NUM_SELECTORS];

typedef struct context_t {
    uint8_t next_param;

    selector_t selectorIndex;
} context_t;

_Static_assert(sizeof(context_t) <= 5 * 32, "Structure of parameters too big.");
