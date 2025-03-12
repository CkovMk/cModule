# Copyright 2025 Chekhov.Ma
#
# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20)

# Initial definition
#   List of absolute path to sources
set(cModule_Source "")
#   List of interface include path
set(cModule_PublicInclude "")
#   List of private include path
set(cModule_Include "")

list(APPEND cModule_PublicInclude
    ${CMAKE_CURRENT_LIST_DIR}/utilities
    ${CMAKE_CURRENT_LIST_DIR}/utilities/extlib/mlib
)

if(DEFINED CONFIG_CMODULE_LIB_CRC32)
    list(APPEND cModule_Source
        ${CMAKE_CURRENT_LIST_DIR}/utilities/lib_crc32.c
    )
endif()

if(DEFINED CONFIG_CMODULE_SYS_RMCALL)
    list(APPEND cModule_Source
        ${CMAKE_CURRENT_LIST_DIR}/utilities/sys_rmcall.c
    )
endif()

if(DEFINED CONFIG_CMODULE_DEVICE_LINUXABI)
    include(d_linuxabi/CMakeLists.txt)
endif()
if(DEFINED CONFIG_CMODULE_DEVICE_MCXA153)
    include(d_mcxa153/CMakeLists.txt)
endif()

# message(STATUS "cModule_Source      =${cModule_Source}")
# message(STATUS "cModule_PublicInclude   =${cModule_PublicInclude}")
# message(STATUS "cModule_Include         =${cModule_Include}")

if(cModuleLib_IS_TOP_LEVEL)

    message(STATUS "cModule: Direct build detected")
    # FIXME: handle Kconfig by ourself, then build the lib.

    project(cModuleLib)

    add_library(cModule STATIC ${cModule_Source})
    target_include_directories(cModule INTERFACE ${cModule_PublicInclude})
    target_include_directories(cModule PRIVATE ${cModule_Include})

elseif(DEFINED MCUX_SDK_PROJECT_NAME) # TODO: better way to challenge MCUX SDK environment

    message(STATUS "cModule: MCUX SDK detected")
    mcux_add_source(
        BASE_PATH /
        SOURCES
            ${cModule_Source}
    )
    mcux_add_include(
        BASE_PATH /
        INCLUDES
            ${cModule_Include}
            ${cModule_PublicInclude}
    )

elseif(DEFINED ZEPHYR_BASE)

    message(STATUS "cModule: Zephyr RTOS detected")
    # TODO: add zephyr project

else()

    message(STATUS "cModule: Custom environment detected")
    message(STATUS "cModule: Global property CMODULE_PARENT_EXECUTABLE must be defined")

    get_property(cModule_ParentExecutable
        GLOBAL PROPERTY
            CMODULE_PARENT_EXECUTABLE
    )

    target_sources(${cModule_ParentExecutable} PRIVATE ${cModule_Source})
    target_include_directories(${cModule_ParentExecutable} PRIVATE ${cModule_PublicInclude})
    target_include_directories(${cModule_ParentExecutable} PRIVATE ${cModule_Include})

endif()
