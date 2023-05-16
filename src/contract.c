#include "kiln_plugin.h"

// V1 - Solo Staking
// --- cast keccak "deposit()"
static const uint32_t KILN_V1_DEPOSIT_SELECTOR = 0xd0e30db0;
// --- cast keccak "withdraw(bytes)"
static const uint32_t KILN_V1_WITHDRAW_SELECTOR = 0x0968f264;
// --- cast keccak "withdrawELFee(bytes)"
static const uint32_t KILN_V1_WITHDRAW_EL_SELECTOR = 0xbf509bd4;
// --- cast keccak "withdrawCLFee(bytes)"
static const uint32_t KILN_V1_WITHDRAW_CL_SELECTOR = 0x2ba03a79;
// --- cast keccak "batchWithdraw(bytes)"
static const uint32_t KILN_V1_BATCH_WITHDRAW_SELECTOR = 0xe8a0c121;
// --- cast keccak "batchWithdrawELFee(bytes)"
static const uint32_t KILN_V1_BATCH_WITHDRAW_EL_SELECTOR = 0xef5e4682;
// --- cast keccak "batchWithdrawCLFee(bytes)"
static const uint32_t KILN_V1_BATCH_WITHDRAW_CL_SELECTOR = 0x0ffab6c2;
// --- cast keccak "requestValidatorsExit(bytes)"
static const uint32_t KILN_V1_REQUEST_EXIT_SELECTOR = 0xb6b06dec;

// V2 - Pooled Staking
// --- cast keccak "stake()"
static const uint32_t KILN_V2_STAKE_SELECTOR = 0x3a4b66f1;
// --- cast keccak "requestExit(uint256)"
static const uint32_t KILN_V2_REQUEST_EXIT_SELECTOR = 0x721c6513;
// --- cast keccak "multiClaim(address[], uint32[][], uint32[][])(int64[][])"
static const uint32_t KILN_V2_MULTICLAIM_SELECTOR = 0xa6d95360;
// --- cast keccak "claim(uint32[] calldata ticketIds, uint32[] calldata caskIds, uint16
// maxClaimDepth)(uint8[])"
static const uint32_t KILN_V2_CLAIM_SELECTOR = 0x10dd50a7;

const uint32_t KILN_V1_SELECTORS[NUM_SELECTORS] = {
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
};
