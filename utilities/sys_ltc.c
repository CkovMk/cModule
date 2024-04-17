/**
 * Copyright 2018 - 2021 HITSIC
 * Copyright 2022 - 2023 Chekhov.Ma
 * All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "sys_ltc.h"

#if (defined(CMODULE_USE_LTC) && (CMODULE_USE_LTC != 0U))

uint64_t LTC_GetTime_us(void)
{
    return COUNT_TO_USEC(PITMGR_GetLTC(), CMODULE_LTC_CLKFREQ);
}

uint64_t LTC_GetTime_ms(void)
{
    return COUNT_TO_MSEC(PITMGR_GetLTC(), CMODULE_LTC_CLKFREQ);
}

void LTC_Delay(uint64_t _t)
{
    uint64_t cnt = PITMGR_GetLTC() + _t;
    while (PITMGR_GetLTC() < cnt);
}

void LTC_Delay_us(uint64_t _t)
{
    uint64_t cnt = PITMGR_GetLTC() + USEC_TO_COUNT(_t, CMODULE_LTC_CLKFREQ);
    while (PITMGR_GetLTC() < cnt);
}

void LTC_Delay_ms(uint64_t _t)
{
    uint64_t cnt = PITMGR_GetLTC() + MSEC_TO_COUNT(_t, CMODULE_LTC_CLKFREQ);
    while (PITMGR_GetLTC() < cnt);
}

#endif // ! CMODULE_USE_LTC
