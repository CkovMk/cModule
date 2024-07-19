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
#include "../cModule/d_mcxa153/sys_rmcall_port.h"

#if defined(CMODULE_USE_RMCALL) && (CMODULE_USE_RMCALL > 0)

#include <sys_rmcall.h>

#define SYSLOG_TAG "RMCALL"
#define SYSLOG_LVL RMCALL_SYSLOG_LVL
#include <inc_syslog.h>

extern rmcall_t rmcall_host;

lpuart_transfer_t UART_rxTransfer =
{
  .rxData = NULL,
  .dataSize = 0
};
lpuart_transfer_t UART_txTransfer =
{
  .data = NULL,
  .dataSize = 0,
};

status_t RMCALL_HOST_Tx(void *_data, uint32_t _dataSize)
{
	UART_txTransfer.data     = (uint8_t *)_data;
	UART_txTransfer.dataSize = _dataSize;
	return LPUART_TransferSendNonBlocking(RMCALL_UART_INST, &BOARD_UART_RMCALL_handle, &UART_txTransfer);
}
status_t RMCALL_HOST_Rx(void *_data, uint32_t _dataSize)
{
	UART_rxTransfer.data     = (uint8_t *)_data;
	UART_rxTransfer.dataSize = _dataSize;
	return LPUART_TransferReceiveNonBlocking(RMCALL_UART_INST, &BOARD_UART_RMCALL_handle, &UART_rxTransfer, NULL);
}
void RMCALL_HOST_TxAbort(void)
{
	LPUART_TransferAbortSend(RMCALL_UART_INST, &BOARD_UART_RMCALL_handle);
}
void RMCALL_HOST_RxAbort(void)
{
	LPUART_TransferAbortReceive(RMCALL_UART_INST, &BOARD_UART_RMCALL_handle);
}

void RMCALL_HOST_CpltCallback(LPUART_Type *base, lpuart_handle_t *handle, status_t status, void *userData)
{
    //(void)(userData);
    if (kStatus_LPUART_TxIdle == status)
    {
        RMCALL_TxIsr(&rmcall_host);
    }

    if (kStatus_LPUART_RxIdle == status)
    {
        RMCALL_RxIsr(&rmcall_host);
    }
}

#endif // CMODULE_USE_RMCALL
