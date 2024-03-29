#include <stdint.h>

#include "fsl_common.h"

uint32_t hal_criticalCnt;
uint32_t hal_regPrimask;

void HAL_EnterCritical(void)
{
    if(0u == hal_criticalCnt++)
    {
        hal_regPrimask = DisableGlobalIRQ();
    }
}

void HAL_ExitCritical(void)
{
    assert(hal_criticalCnt);
    if(--hal_criticalCnt == 0u)
    {
        EnableGlobalIRQ(hal_regPrimask);
    }
}