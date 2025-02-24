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
#ifndef D_MCXA153_SYS_RMCALL_PORT_H
#define D_MCXA153_SYS_RMCALL_PORT_H
#include "peripherals.h"

#include "cmodule_common.h"
//#include "inc_stdlib.h"

#if defined(CMODULE_USE_RMCALL) && (CMODULE_USE_RMCALL > 0)

#define RMCALL_UART_INST BOARD_UART_RMCALL_PERIPHERAL
extern lpuart_handle_t BOARD_UART_RMCALL_handle;

#define RMCALL_HEADER_MAGIC (0x554768A0U)
#define RMCALL_SYSLOG_LVL (3U)
#define RMCALL_PUBLIC_BUF_SIZE (256U)
#define mStatusGroup_RMCALL (201U)

#define RMCALL_TRAILER_CRC32 (1U)

// TODO: implement this
#define RMCALL_USE_GENERIC_HANDLE (0U) // a generic handle, called when no maching id or parity error.

status_t RMCALL_HOST_Tx(void *_data, uint32_t _dataSize);
status_t RMCALL_HOST_Rx(void *_data, uint32_t _dataSize);
void RMCALL_HOST_TxAbort(void);
void RMCALL_HOST_RxAbort(void);

void RMCALL_HOST_CpltCallback(LPUART_Type *base, lpuart_handle_t *handle, status_t status, void *userData);

#endif // CMODULE_USE_RMCALL

#endif // ! D_MCXA153_SYS_RMCALL_PORT_H
