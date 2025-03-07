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
#ifndef D_LINUXABI_INC_SYSLOG_PORT_H
#define D_LINUXABI_INC_SYSLOG_PORT_H

#include "cmodule_common.h"
#include <stdio.h>

#ifdef DEBUG
#define SYSLOG_DEBUG
#endif

#define CMODULE_LOG_PRINTF(...)  (printf(__VA_ARGS__))

#define CMODULE_LOG_LINEFEED ("\n")

#endif // ! D_LINUXABI_INC_SYSLOG_PORT_H
