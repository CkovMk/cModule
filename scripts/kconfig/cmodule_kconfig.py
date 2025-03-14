# Copyright 2025 Chekhov.Ma
# SPDX-License-Identifier: Apache-2.0
#
# Originally modified from: https://git.trustedfirmware.org/cModule/trusted-firmware-m
# Original licensing information:
#-------------------------------------------------------------------------------
# Copyright (c) 2022-2023, Arm Limited. All rights reserved.
# SPDX-License-Identifier: BSD-3-Clause
#
#-------------------------------------------------------------------------------

import argparse
import logging
import os
import re

from kconfiglib import Kconfig, TRI_TO_STR, BOOL, TRISTATE
import menuconfig
import guiconfig

# NOTE: in_component_label is related with Kconfig menu prompt.
in_component_label = 'cModule library configs'
prefix = 'CONFIG_'

def parse_args():
    parser = argparse.ArgumentParser(description=\
            'cModule Kconfig tool generates CMake configurations and header file \
             component configurations. Terminal UI and GUI can help quickly \
             configurate cModule build options.')

    parser.add_argument(
        '-k', '--kconfig-file',
        dest = 'kconfig_file',
        required = True,
        help = 'The Top-level Kconfig file'
    )

    parser.add_argument(
        '-o', '--output-path',
        dest = 'output_path',
        required = True,
        help = 'The output file folder'
    )

    parser.add_argument(
        '--envs',
        dest='envs',
        default = None,
        nargs = '*',
        help = 'The environment variables for Kconfig files. Use absolute paths for directories.\
                The format must be key-value pairs with "=" in the middle, for example:\
                FOO=foo BAR=bar'
    )

    parser.add_argument(
        '--config-files',
        dest='config_files',
        default = None,
        nargs = '*',
        help = 'The config files to be load and merge. The load order is the same as this list order,\
                The later ones override the former ones.\
                If .config is found in output-path, this file list is ignored.'
    )

    parser.add_argument(
        '-u', '--ui',
        dest = 'ui',
        required = False,
        default = None,
        choices = ['gui', 'tui'],
        help = 'Which config UI to display'
    )

    args = parser.parse_args()

    return args

def set_env_var(envs):
    '''
    The Kconfig files might use some environment variables.
    This method sets environment variables for Kconfig files.
    Each item in 'envs' should be in the key-value format, for example:
    'FOO=foo BAR=bar'
    '''
    if envs is None:
        return

    for env in envs:
        env_entries = env.strip('\r\n').split()
        for _env in env_entries:
            key, value = _env.split('=')
            os.environ[key] = value

def generate_file(dot_config):
    '''
    The .config file is the generated result from Kconfig files. It contains
    the set and un-set configs and their values.

    cModule splits the configs to build options and component options. The former
    will be written into CMake file. The latter are all under a menu which has
    the prompt which contains in_component_label. These configs will be written
    into header file.
    '''

    output_dir = os.path.dirname(dot_config)
    cmake_file = os.path.join(output_dir, 'project_config.cmake')
    header_file = os.path.join(output_dir, 'project_config.h')

    in_component_options, menu_start = False, False

    '''
    The regular expression is used to parse the text like:
        - CONFIG_FOO=val
        - # CONFIG_FOO is not set
    The 'FOO' will be saved into the name part of groupdict, and the 'val' will
    be saved into the 'val' part of groupdict.
    '''
    pattern_set = re.compile('CONFIG_(?P<name>[A-Za-z|_|0-9]*)=(?P<val>\\S+)')
    pattern_not_set = re.compile('# CONFIG_(?P<name>[A-Za-z|_|0-9]*) is not set')

    with open(cmake_file, 'w') as f_cmake, open(header_file, 'w') as f_header, \
                                           open(dot_config, 'r') as f_config:

        for line in f_config:
            '''
            Extract in_component_options flag from start line and end line
            which has the in_component_label.
            '''
            if line.startswith('# ' + in_component_label):
                in_component_options = True
                continue
            if line.startswith('end of ' + in_component_label):
                in_component_options =False
                continue

            '''
            Extract the menu prompt. It forms like:
                ...
                    #
                # FOO Module
                #
                ...
            Here get the text 'FOO Module', and write it as comment in
            output files.
            '''
            if line == '#\n' and not menu_start:
                menu_start = True
                continue
            if line == '#\n' and menu_start:
                menu_start = False
                continue

            # Write the menu prompt.
            if menu_start:
                f_cmake.write('\n# {}\n'.format(line[2:-1]))
                f_header.write('\n/* {} */\n'.format(line[2:-1]))
                continue

            '''
            Parse dot_config text by regular expression and get the config's
            name, value and type. Then write the result into CMake and
            header files.

            CONFIG_FOO=y
                - CMake:  set(FOO ON CACHE BOOL '')
                - Header: #define FOO 1
            CONFIG_FOO='foo'
                - CMake:  set(FOO 'foo' CACHE STRING '')
                - Header: #define FOO 'foo'
            # CONFIG_FOO is not set
                - CMake:  set(FOO OFF CACHE BOOL '')
                - Header: #define FOO 0
            '''
            name, cmake_type, cmake_val, header_val = '', '', '', ''

            # Search the configs set by Kconfig.
            ret = pattern_set.match(line)
            if ret:
                name = ret.groupdict()['name']
                val = ret.groupdict()['val']
                if val == 'y':
                    cmake_val = 'ON'
                    cmake_type = 'BOOL'
                    header_val = '1'
                else:
                    cmake_val = val
                    cmake_type = 'STRING'
                    header_val = val

            # Search the not set configs.
            ret = pattern_not_set.match(line)
            if ret:
                name = ret.groupdict()['name']
                cmake_val = 'OFF'
                cmake_type = 'BOOL'
                header_val = '0'

            # Write the result into cmake and header files.
            if name:
                if cmake_val == 'OFF':
                    f_cmake.write('unset({:<45} {:<15} CACHE {:<15})\n'.
                              format(prefix + name, '', ''))
                elif cmake_val == 'ON':
                    f_cmake.write('set(  {:<45} {:<15} CACHE {:<6} "" FORCE)\n'.
                              format(prefix + name, '', cmake_type))
                else:
                    f_cmake.write('set(  {:<45} {:<15} CACHE {:<6} "" FORCE)\n'.
                              format(prefix + name, cmake_val, cmake_type))
                f_header.write('#define {:<45} {}\n'.format(prefix + name, header_val))

    logging.info('cModule build configs saved to \'{}\''.format(cmake_file))
    logging.info('cModule component configs saved to \'{}\''.format(header_file))

def validate_promptless_sym(kconfig):
    """
    Check if any assignments to promptless symbols.
    """

    ret = True

    for sym in kconfig.unique_defined_syms:
        if sym.user_value and not any(node.prompt for node in sym.nodes):
            logging.error('Assigning value to promptless symbol {}'.format(sym.name))
            ret = False

    return ret

def validate_assigned_sym(kconfig):
    """
    Checks if all assigned symbols have the expected values
    """

    ret = True

    for sym in kconfig.unique_defined_syms:
        if not sym.user_value:
            continue

        if sym.type in (BOOL, TRISTATE):
            user_val = TRI_TO_STR[sym.user_value]
        else:
            user_val = sym.user_value

        if user_val != sym.str_value:
            logging.error('Tried to set [{}] to <{}>, but is <{}> finally.'.format(
                            sym.name, user_val, sym.str_value))
            ret = False

    return ret

if __name__ == '__main__':
    logging.basicConfig(format='[%(filename)s] %(levelname)s: %(message)s',
                        level = logging.INFO)

    args = parse_args()

    # dot_config has a fixed name. Do NOT rename it.
    dot_config = os.path.abspath(os.path.join(args.output_path, '.config'))
    mtime_prv = 0

    set_env_var(args.envs)

    # Load Kconfig file. kconfig_file is the root Kconfig file. The path is
    # input by users from the command.
    tfm_kconfig = Kconfig(args.kconfig_file)
    tfm_kconfig.disable_undef_warnings() # Disable warnings for undefined symbols when loading
    tfm_kconfig.disable_override_warnings() # Overriding would happen when loading multiple config files
    tfm_kconfig.disable_redun_warnings() # Redundant definitions might happen when loading multiple config files

    if not os.path.exists(args.output_path):
        os.mkdir(args.output_path)

    if os.path.exists(dot_config):
        # Load .config which contains the previous configurations.
        # Input config files are ignored.
        logging.info('.config file found, other config files are ignored.')
        mtime_prv = os.stat(dot_config).st_mtime
        logging.info(tfm_kconfig.load_config(dot_config))
    elif args.config_files is not None:
        # Load input config files if .config is not found and write the .config file.
        for conf in args.config_files:
            logging.info(tfm_kconfig.load_config(conf, replace = False))

        if not validate_promptless_sym(tfm_kconfig) or not validate_assigned_sym(tfm_kconfig):
            exit(1)

    # Change program execution path to the output folder path because menuconfigs do not support
    # writing .config to arbitrary folders.
    os.chdir(args.output_path)

    # UI options
    if args.ui == 'tui':
        menuconfig.menuconfig(tfm_kconfig)
    elif args.ui == 'gui':
        guiconfig.menuconfig(tfm_kconfig)
    else:
        logging.info(tfm_kconfig.write_config(dot_config))

    if not os.path.exists(dot_config):
        # This could happend when the user did not "Save" the config file when using menuconfig
        # We should abort here in such case.
        logging.error('No .config is saved!')
        exit(1)

    # Generate output files if .config has been changed.
    if os.stat(dot_config).st_mtime != mtime_prv:
        generate_file(dot_config)
