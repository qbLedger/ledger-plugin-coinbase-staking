#include "kiln_plugin.h"

// Selector is the MethodId on Ethercan
static const uint32_t KILN_DEPOSIT_SELECTOR = 0xf340fa01;
static const uint32_t KILN_WITHDRAW_SELECTOR = 0x0968f264;
static const uint32_t KILN_WITHDRAW_EL_SELECTOR = 0xbf509bd4;
static const uint32_t KILN_WITHDRAW_CL_SELECTOR = 0x2ba03a79;

const uint32_t KILN_SELECTORS[NUM_SELECTORS] = {KILN_DEPOSIT_SELECTOR,
                                                KILN_WITHDRAW_SELECTOR,
                                                KILN_WITHDRAW_EL_SELECTOR,
                                                KILN_WITHDRAW_CL_SELECTOR};

