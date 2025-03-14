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
#ifndef D_LINUXABI_SYS_RMCALL_PORT_H
#define D_LINUXABI_SYS_RMCALL_PORT_H
#include "cmodule_common.h"

// Linux headers
#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()

#include <stdlib.h>
#include <pthread.h>
#include <signal.h>

#if defined(CMODULE_USE_RMCALL) && (CMODULE_USE_RMCALL > 0)

#define RMCALL_HEADER_MAGIC (CONFIG_RMCALL_HEADER_MAGIC)
//#define RMCALL_HEADER_RX_MAGIC (0x554768A0U)
//#define RMCALL_HEADER_TX_MAGIC (0x554768A0U)
#define RMCALL_SYSLOG_LVL (CONFIG_RMCALL_SYSLOG_LVL)
#define RMCALL_PUBLIC_BUF_SIZE (CONFIG_RMCALL_PUBLIC_BUFFER_SIZE)
#define mStatusGroup_RMCALL (201U)

#define RMCALL_TRAILER_CRC32 (CONFIG_RMCALL_TRAILER_CRC32)

// TODO: implement this
#define RMCALL_USE_GENERIC_HANDLE (0U) // a generic handle, called when no maching id or parity error.

#ifdef __cplusplus
extern "C" {
#endif

mstatus_t RMCALL_HOST_Tx(void *_data, uint32_t _dataSize);
mstatus_t RMCALL_HOST_Rx(void *_data, uint32_t _dataSize);
void RMCALL_HOST_TxAbort(void);
void RMCALL_HOST_RxAbort(void);

#ifdef __cplusplus
}
#endif

#endif // CMODULE_USE_RMCALL

#endif // ! D_LINUXABI_SYS_RMCALL_PORT_H
