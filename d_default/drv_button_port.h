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
#ifndef D_DEFAULT_DRV_BUTTON_PORT_H
#define D_DEFAULT_DRV_BUTTON_PORT_H
#include "cmodule_common.h"
#include "sys_extint.hpp"
#include "sys_pitmgr.hpp"

#if defined(CMODULE_USE_DRV_BUTTON) && (CMODULE_USE_DRV_BUTTON > 0)

#define BUTTON_TIME_SHRT 50u     //short press
#define BUTTON_SHRT_TOUT 200u   //short timeout
#define BUTTON_TIME_LONG 500u   //long press
#define BUTTON_TIME_LRPT 100u   //long press repeat, time calculated from key press. the actual time for repeat will be REPT-LONG
#define BUTTON_REPT_TOUT 550u   //repeat timeout
#define BUTTON_TIME_INTV 50u

#define BUTTON_PRESSDN_LOGIC 0u
#define BUTTON_RELEASE_LOGIC 1u
#define BUTTON_PRESSDN_EXTINT EXTINT_InterruptFallingEdge //define which edge indicates button pressed.
#define BUTTON_RELEASE_EXTINT EXTINT_InterruptRisingEdge  //define which edge indicates button release.

#define BUTTON_PITMGR_TIME_MS 10

#define BUTTON_TIMER_MS     (pitMgr_t::timer_ms)

#endif // ! CMODULE_USE_DRV_BUTTON

#endif // ! D_DEFAULT_DRV_BUTTON_PORT_H
