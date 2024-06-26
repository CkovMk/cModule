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
#ifndef CMODULE_INC_STATUS_H
#define CMODULE_INC_STATUS_H

#include <stdint.h>

/*! @brief Construct a status code value from a group and code number. */
#define CMODULE_MAKE_STATUS(group, code) ((((group)*100) + (code)))

/*! @brief Construct the version number for modules. */
#define CMODULE_MAKE_VERSION(major, minor, patch) (((major) << 16) | ((minor) << 8) | (patch))
#define CMODULE_VERSION_MAJOR(x) (x >> 16U)
#define CMODULE_VERSION_MINOR(x) ((x >> 8U) & 0xffU)
#define CMODULE_VERSION_PATCH(x) (x & 0xffU)

/*! @brief Status group numbers. */
enum _cmodule_status_groups
{
    mStatusGroup_Generic = 0,                 /*!< Group number for generic status codes. */
};

/*! \public
 * @brief Generic status return codes.
 */
enum
{
    mStatus_Success = CMODULE_MAKE_STATUS(mStatusGroup_Generic, 0),  /*!< Generic status for Success. */
    mStatus_Fail = CMODULE_MAKE_STATUS(mStatusGroup_Generic, 1),      /*!< Generic status for Fail. */
    mStatus_ReadOnly = CMODULE_MAKE_STATUS(mStatusGroup_Generic, 2),    /*!< Generic status for read only failure. */
    mStatus_OutOfRange = CMODULE_MAKE_STATUS(mStatusGroup_Generic, 3),   /*!< Generic status for out of range access. */
    mStatus_InvalidArgument = CMODULE_MAKE_STATUS(mStatusGroup_Generic, 4),   /*!< Generic status for invalid argument check. */
    mstatus_timeout = CMODULE_MAKE_STATUS(mStatusGroup_Generic, 5),   /*!< Generic status for timeout. */
    mStatus_NoTransferInProgress = CMODULE_MAKE_STATUS(mStatusGroup_Generic, 6),   /*!< Generic status for no transfer in progress. */
};

/*! @brief Type used for all status and error return values. */
typedef int32_t mstatus_t;

#endif // ! CMODULE_INC_STATUS_H
