#include "kiln_plugin.h"

// ONCHAIN V1 - Solo Staking
// --- cast sig "deposit()"
static const uint32_t KILN_V1_DEPOSIT_SELECTOR = 0xd0e30db0;
// --- cast sig "withdraw(bytes)"
static const uint32_t KILN_V1_WITHDRAW_SELECTOR = 0x0968f264;
// --- cast sig "withdrawELFee(bytes)"
static const uint32_t KILN_V1_WITHDRAW_EL_SELECTOR = 0xbf509bd4;
// --- cast sig "withdrawCLFee(bytes)"
static const uint32_t KILN_V1_WITHDRAW_CL_SELECTOR = 0x2ba03a79;
// --- cast sig "batchWithdraw(bytes)"
static const uint32_t KILN_V1_BATCH_WITHDRAW_SELECTOR = 0xe8a0c121;
// --- cast sig "batchWithdrawELFee(bytes)"
static const uint32_t KILN_V1_BATCH_WITHDRAW_EL_SELECTOR = 0xef5e4682;
// --- cast sig "batchWithdrawCLFee(bytes)"
static const uint32_t KILN_V1_BATCH_WITHDRAW_CL_SELECTOR = 0x0ffab6c2;
// --- cast sig "requestValidatorsExit(bytes)"
static const uint32_t KILN_V1_REQUEST_EXIT_SELECTOR = 0xb6b06dec;

// ONCHAIN V2 - Pooled Staking
// --- cast sig "stake()"
static const uint32_t KILN_V2_STAKE_SELECTOR = 0x3a4b66f1;
// --- cast sig "requestExit(uint256)"
static const uint32_t KILN_V2_REQUEST_EXIT_SELECTOR = 0x721c6513;
// --- cast sig "multiClaim(address[],uint256[][],uint32[][])"
static const uint32_t KILN_V2_MULTICLAIM_SELECTOR = 0xb7ba18c7;
// --- cast sig "claim(uint256[],uint32[],uint16)"
static const uint32_t KILN_V2_CLAIM_SELECTOR = 0xadcf1163;

// RESTAKING - Liquid Restaking
// --- cast sig "approve(address,uint256)"
static const uint32_t KILN_LR_ERC20_APPROVE_SELECTOR = 0x095ea7b3;
// --- cast sig "depositIntoStrategy(address,address,uint256)"
static const uint32_t KILN_LR_DEPOSIT_INTO_STRATEGY_SELECTOR = 0xe7a050aa;
// --- cast sig "queueWithdrawal(uint256[],address[],uint256[],address,bool)"
static const uint32_t KILN_LR_QUEUE_WITHDRAWAL_SELECTOR = 0xf123991e;
// --- cast sig "queueWithdrawals((address[],uint256[],address)[])"
static const uint32_t KILN_LR_QUEUE_WITHDRAWALS_SELECTOR = 0x0dd8dd02;
// --- cast sig "completeQueuedWithdrawal((address,address,address,uint256,uint32,address[],uint256[]),address[],uint256,bool)"
static const uint32_t KILN_LR_COMPLETE_QUEUED_WITHDRAWAL_SELECTOR = 0x60d7faed;
// --- cast sig "completeQueuedWithdrawals((address,address,address,uint256,uint32,address[],uint256[])[],address[][],uint256[],bool[])"
static const uint32_t KILN_LR_COMPLETE_QUEUED_WITHDRAWALS_SELECTOR = 0x33404396;


const uint32_t KILN_SELECTORS[NUM_SELECTORS] = {
    // V1
    KILN_V1_DEPOSIT_SELECTOR,
    KILN_V1_WITHDRAW_SELECTOR,
    KILN_V1_WITHDRAW_EL_SELECTOR,
    KILN_V1_WITHDRAW_CL_SELECTOR,
    KILN_V1_BATCH_WITHDRAW_SELECTOR,
    KILN_V1_BATCH_WITHDRAW_EL_SELECTOR,
    KILN_V1_BATCH_WITHDRAW_CL_SELECTOR,
    KILN_V1_REQUEST_EXIT_SELECTOR,
    // V2
    KILN_V2_STAKE_SELECTOR,
    KILN_V2_REQUEST_EXIT_SELECTOR,
    KILN_V2_MULTICLAIM_SELECTOR,
    KILN_V2_CLAIM_SELECTOR,
    // LR
    KILN_LR_ERC20_APPROVE_SELECTOR,
    KILN_LR_DEPOSIT_INTO_STRATEGY_SELECTOR,
    KILN_LR_QUEUE_WITHDRAWAL_SELECTOR,
    KILN_LR_QUEUE_WITHDRAWALS_SELECTOR,
    KILN_LR_COMPLETE_QUEUED_WITHDRAWAL_SELECTOR,
    KILN_LR_COMPLETE_QUEUED_WITHDRAWALS_SELECTOR
};
