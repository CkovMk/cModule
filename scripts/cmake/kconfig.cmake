# Copyright 2025 Chekhov.Ma
#
# SPDX-License-Identifier: Apache-2.0

find_package (Python3 COMPONENTS Interpreter)

set(KCONFIG_SCRIPT ${CMAKE_CURRENT_LIST_DIR}/../kconfig/cmodule_kconfig.py)
set(KCONFIG_ROOT_FILE ${CMAKE_CURRENT_LIST_DIR}/../../Kconfig)
get_property(KCONFIG_CONF_FILE_LIST
    GLOBAL PROPERTY
        KCONFIG_CONF_FILE_LIST
)
set(KCONFIG_MERGED_CONF ${CMAKE_CURRENT_BINARY_DIR}/.config)
set(KCONFIG_GENERATED_HEADER ${CMAKE_CURRENT_BINARY_DIR}/project_config.h)
set(KCONFIG_GENERATED_CMAKE ${CMAKE_CURRENT_BINARY_DIR}/project_config.cmake)

#message(STATUS "Kconfig root file: ${KCONFIG_ROOT_FILE}")
#message(STATUS "Kconfig config files: ${KCONFIG_CONF_FILE_LIST}")

# run script to generate files
execute_process(
    COMMAND
        ${Python3_EXECUTABLE} ${KCONFIG_SCRIPT} -k ${KCONFIG_ROOT_FILE} -o ${CMAKE_CURRENT_BINARY_DIR} --config-files ${KCONFIG_CONF_FILE_LIST}
    WORKING_DIRECTORY
        ${CMAKE_CURRENT_BINARY_DIR}
    RESULT_VARIABLE
        KCONFIG_RESULT
)
if(${KCONFIG_RESULT})
    message(FATAL_ERROR "kconfig failed with error ${KCONFIG_RESULT}.")
endif()

# include generated files in cmake and sources
include(${KCONFIG_GENERATED_CMAKE})
if(CMAKE_C_COMPILER_ID MATCHES "GNU|CLANG")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -include ${KCONFIG_GENERATED_HEADER}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -include ${KCONFIG_GENERATED_HEADER}")
else()
    message(WARNING "Unsupported compiler. Cannot automatically include kconfig header")
endif()
