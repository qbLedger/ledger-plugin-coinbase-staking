#include "kiln_plugin.h"

// cast keccak "deposit()"
static const uint32_t KILN_DEPOSIT_SELECTOR = 0xd0e30db0;
// cast keccak "withdraw(bytes)"
static const uint32_t KILN_WITHDRAW_SELECTOR = 0x0968f264;
// cast keccak "withdrawELFee(bytes)"
static const uint32_t KILN_WITHDRAW_EL_SELECTOR = 0xbf509bd4;
// cast keccak "withdrawCLFee(bytes)"
static const uint32_t KILN_WITHDRAW_CL_SELECTOR = 0x2ba03a79;

const uint32_t KILN_SELECTORS[NUM_SELECTORS] = {KILN_DEPOSIT_SELECTOR,
                                                KILN_WITHDRAW_SELECTOR,
                                                KILN_WITHDRAW_EL_SELECTOR,
                                                KILN_WITHDRAW_CL_SELECTOR};
