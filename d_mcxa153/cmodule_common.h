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
#ifndef D_MCXA153_CMODULE_COMMON_H
#define D_MCXA153_CMODULE_COMMON_H

#define __PACKED __attribute__((packed))
#define __WEAK __attribute__((weak))

#include "stdint.h"
#include "inc_mstatus.h"
#include <fsl_common.h>

/**
 * @brief : 软件版本产生方式定义
 */
#define CMODULE_MAKE_VERSION(major, minor, patch) (((major) << 16) | ((minor) << 8) | (patch))
#define CMODULE_VERSION_MAJOR(x) (x >> 16U)
#define CMODULE_VERSION_MINOR(x) ((x >> 8U) & 0xffU)
#define CMODULE_VERSION_PATCH(x) (x & 0xffU)

/** SYS */

#ifndef CMODULE_USE_RMCALL
#define CMODULE_USE_RMCALL 		(1U)
#endif // ! CMODULE_USE_RMCALL

#ifdef __cplusplus
extern "C"{
#endif

void HAL_EnterCritical(void);

void HAL_ExitCritical(void);

#ifdef __cplusplus
}
#endif

#endif // ! D_MCXA153_CMODULE_COMMON_H
