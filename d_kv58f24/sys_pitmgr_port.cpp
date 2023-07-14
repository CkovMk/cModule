/*
 * sys_pitmgr_port.cpp
 *
 *  Created on: 2019年12月5日
 *      Author: CkovMk
 */

#include "sys_pitmgr.hpp"


#if defined(CMODULE_USE_PITMGR) && (CMODULE_USE_PITMGR > 0)

#ifdef __cplusplus
extern "C"{
#endif

#if defined(CMODULE_PITMGR_DEFAULT_IRQ) && (CMODULE_PITMGR_DEFAULT_IRQ > 0)
void LPTMR0_IRQHandler(void)
{
	PIT_ClearStatusFlags(PIT, kPIT_Chnl_2, kPIT_TimerFlag);
	pitMgr_t::isr();
}
#endif // ! HTISIC_PITMGR_USE_IRQHANDLER

#ifdef __cplusplus
}
#endif




#endif // ! CMODULE_USE_PITMGR
