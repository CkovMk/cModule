# Copyright 2025 Chekhov.Ma
#
# SPDX-License-Identifier: Apache-2.0

list(APPEND cModule_Source
    ${CMAKE_CURRENT_LIST_DIR}/cmodule_common.c
)

list(APPEND cModule_Include
    ${CMAKE_CURRENT_LIST_DIR}
)

if(DEFINED CONFIG_CMODULE_SYS_RMCALL)
    list(APPEND cModule_Source
        ${CMAKE_CURRENT_LIST_DIR}/sys_rmcall_port.c
    )
endif()
