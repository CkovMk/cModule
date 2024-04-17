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
#ifndef UTILITIES_LIB_CRC32_H
#define UTILITIES_LIB_CRC32_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/*!
 * @addtogroup pidctrl
 * @{
 */

/** @brief : 软件版本 */
//#define LIB_CRC32_VERSION (CMODULE_MAKE_VERSION(0U, 1U, 0U))

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Compute the 32-bit CRC.
 *
 * This CRC can be specified as:
 * Width  : 32
 * Poly   : 0x04c11db7
 * Init   : parameter, typically 0xffffffff
 * RefIn  : false
 * RefOut : false
 * XorOut : 0
 * This differs from the "standard" CRC-32 algorithm in that the values
 * are not reflected, and there is no final XOR value.  These differences
 * make it easy to compose the values of multiple blocks.
 *
 * @param buf Data buffer.
 * @param len Length in bytes of the data buffer.
 * @param init The starting value.
 * @return uint32_t CRC result.
 */
uint32_t CRC32_Calculate (void const *data, int32_t len, uint32_t init);

#ifdef __cplusplus
}
#endif

/*! @} */


#endif // UTILITIES_LIB_CRC32_H
