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
#ifndef UTILITIES_INC_BITOP_H
#define UTILITIES_INC_BITOP_H

#define  bitSet(value, bit)   ((value) |= (1UL << (bit)))
#define  bitClr(value, bit)   ((value) &= ~(1UL << (bit)))
#define  bitRd(value, bit)   (((value) >> (bit)) & 0x01)
#define  bitWr(value, bit, bitvalue)   (bitvalue ? bitSet(value, bit) : bitClr(value, bit))
#define  bit(b)   (1 << (b))

#endif // ! UTILITIES_INC_BITOP_H
