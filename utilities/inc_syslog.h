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
#ifdef UTILITIES_INC_SYSLOG_H

#undef UTILITIES_INC_SYSLOG_H

#undef SYSLOG_PRINTF_A(...)
#undef SYSLOG_PRINTF_E(...)
#undef SYSLOG_PRINTF_W(...)
#undef SYSLOG_PRINTF_I(...)
#undef SYSLOG_PRINTF_D(...)
#undef SYSLOG_PRINTF_V(...)
#undef SYSLOG_A(...)
#undef SYSLOG_E(...)
#undef SYSLOG_W(...)
#undef SYSLOG_I(...)
#undef SYSLOG_D(...)
#undef SYSLOG_V(...)

#endif // ! UTILITIES_INC_SYSLOG_H

#ifndef UTILITIES_INC_SYSLOG_H
#define UTILITIES_INC_SYSLOG_H

#include <inc_syslog_port.h>
//#define SYSLOG_TAG ("DUMMY")
//#define SYSLOG_LVL (2U)

#ifndef SYSLOG_TAG
#error "SYSLOG_TAG Undefined!"
#endif // ! SYSLOG_TAG

#ifndef SYSLOG_LVL
#error "SYSLOG_LVL Undefined!"
#endif // ! SYSLOG_LVL

#ifndef SYSLOG_LVL_A
#define SYSLOG_LVL_A    (0U)
#endif
#ifndef SYSLOG_LVL_E
#define SYSLOG_LVL_E    (1U)
#endif
#ifndef SYSLOG_LVL_W
#define SYSLOG_LVL_W    (2U)
#endif
#ifndef SYSLOG_LVL_I
#define SYSLOG_LVL_I    (3U)
#endif
#ifndef SYSLOG_LVL_D
#define SYSLOG_LVL_D    (4U)
#endif
#ifndef SYSLOG_LVL_V
#define SYSLOG_LVL_V    (5U)
#endif

#if defined(SYSLOG_DEBUG) && (SYSLOG_LVL >= SYSLOG_LVL_E)
#define SYSLOG_PRINTF_E(...)         CMODULE_LOG_PRINTF(__VA_ARGS__)
#else
#define SYSLOG_PRINTF_E(...) (0U)
#endif // SYSLOG_LVL_E

#if defined(SYSLOG_DEBUG) && (SYSLOG_LVL >= SYSLOG_LVL_W)
#define SYSLOG_PRINTF_W(...)         CMODULE_LOG_PRINTF(__VA_ARGS__)
#else
#define SYSLOG_PRINTF_W(...) (0U)
#endif // SYSLOG_LVL_E

#if defined(SYSLOG_DEBUG) && (SYSLOG_LVL >= SYSLOG_LVL_I)
#define SYSLOG_PRINTF_I(...)         CMODULE_LOG_PRINTF(__VA_ARGS__)
#else
#define SYSLOG_PRINTF_I(...) (0U)
#endif // SYSLOG_LVL_E

#if defined(SYSLOG_DEBUG) && (SYSLOG_LVL >= SYSLOG_LVL_D)
#define SYSLOG_PRINTF_D(...)         CMODULE_LOG_PRINTF(__VA_ARGS__)
#else
#define SYSLOG_PRINTF_D(...) (0U)
#endif // SYSLOG_LVL_E

#if defined(SYSLOG_DEBUG) && (SYSLOG_LVL >= SYSLOG_LVL_V)
#define SYSLOG_PRINTF_V(...)         CMODULE_LOG_PRINTF(__VA_ARGS__)
#else
#define SYSLOG_PRINTF_V(...) (0U)
#endif // SYSLOG_LVL_E



#if defined(SYSLOG_DEBUG)
#define SYSLOG_A(...)         (CMODULE_LOG_PRINTF("[A]") + CMODULE_LOG_PRINTF(SYSLOG_TAG) + CMODULE_LOG_PRINTF(": ") + CMODULE_LOG_PRINTF(__VA_ARGS__) + CMODULE_LOG_PRINTF(CMODULE_LOG_LINEFEED))

#define SYSLOG_E(...)         (SYSLOG_PRINTF_E("[E]") + SYSLOG_PRINTF_E(SYSLOG_TAG) + SYSLOG_PRINTF_E(": ") + SYSLOG_PRINTF_E(__VA_ARGS__) + SYSLOG_PRINTF_E(CMODULE_LOG_LINEFEED))

#define SYSLOG_W(...)         (SYSLOG_PRINTF_W("[W]") + SYSLOG_PRINTF_W(SYSLOG_TAG) + SYSLOG_PRINTF_W(": ") + SYSLOG_PRINTF_W(__VA_ARGS__) + SYSLOG_PRINTF_W(CMODULE_LOG_LINEFEED))

#define SYSLOG_I(...)         (SYSLOG_PRINTF_I("[I]") + SYSLOG_PRINTF_I(SYSLOG_TAG) + SYSLOG_PRINTF_I(": ") + SYSLOG_PRINTF_I(__VA_ARGS__) + SYSLOG_PRINTF_I(CMODULE_LOG_LINEFEED))

#define SYSLOG_D(...)         (SYSLOG_PRINTF_D("[D]") + SYSLOG_PRINTF_D(SYSLOG_TAG) + SYSLOG_PRINTF_D(": ") + SYSLOG_PRINTF_D(__VA_ARGS__) + SYSLOG_PRINTF_D(CMODULE_LOG_LINEFEED))

#define SYSLOG_V(...)         (SYSLOG_PRINTF_V("[V]") + SYSLOG_PRINTF_V(SYSLOG_TAG) + SYSLOG_PRINTF_V(": ") + SYSLOG_PRINTF_V(__VA_ARGS__) + SYSLOG_PRINTF_V(CMODULE_LOG_LINEFEED))

#else

#define SYSLOG_A(...) (0U)
#define SYSLOG_E(...) (0U)
#define SYSLOG_W(...) (0U)
#define SYSLOG_I(...) (0U)
#define SYSLOG_D(...) (0U)
#define SYSLOG_V(...) (0U)

#endif // ! SYSLOG_DEBUG

#endif // ! UTILITIES_INC_SYSLOG_H
