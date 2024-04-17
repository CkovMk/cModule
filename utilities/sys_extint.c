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
#include <sys_extint.h>

#if defined(CMODULE_USE_EXTINT) && (CMODULE_USE_EXTINT > 0)

/*!
 * @addtogroup extint
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

status_t EXTINT_Init(extint_t *_inst)
{
    assert(_inst);

    HAL_EnterCritical();
    extint_isrList_init(_inst->isrList);

    HAL_ExitCritical();

}

void EXTINT_Deinit(extint_t *_inst)
{
    assert(_inst);

    HAL_EnterCritical();
    extint_isrList_clear(_inst->isrList);
    HAL_ExitCritical();
}


void EXTINT_Isr(extint_t *_inst, uint32_t flag)
{
    assert(_inst);

    extint_isrList_it_t it;
    for (extint_isrList_it(it, _inst->isrList); !extint_isrList_end_p(it); extint_isrList_next(it))
    {
        extint_handle_t *handle = *extint_isrList_ref(it);
        if (flag & (1 << handle->index))
        {
            (*(handle->handler))(handle->userData);
        }
    }
}


status_t EXTINT_HandleInsert(extint_t *_inst, extint_handle_t *_handle)
{
    assert(_inst);
    assert(_handle);

    HAL_EnterCritical();
    extint_isrList_push_back(_inst->isrList, _handle);
    HAL_ExitCritical();

    return mStatus_Success;
}


status_t EXTINT_HandleRemove(extint_t *_inst, extint_handle_t *_handle)
{
    HAL_EnterCritical();
    extint_isrList_it_t it;
    for (extint_isrList_it(it, _inst->isrList); !extint_isrList_end_p(it); extint_isrList_next(it))
    {
        if (*extint_isrList_cref(it) == _handle)
        {
            extint_isrList_remove(_inst->isrList, it);
            HAL_ExitCritical();
            return mStatus_Success;
        }
    }
    HAL_ExitCritical();
    return mStatus_Fail;
}

#ifdef __cplusplus
}
#endif

/* @} */

#endif // ! CMODULE_USE_EXTINT
