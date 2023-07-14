/**
 * Copyright 2018 - 2020 HITSIC
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

#ifndef D_RT1052_DRV_IMU_PORT_H_
#define D_RT1052_DRV_IMU_PORT_H_

#include "inc_stdlib.h"
#include "cmodule_common.h"

#define CMODULE_USE_DRV_IMU_INV (0U)





#if defined(CMODULE_USE_DRV_IMU_INV) && (CMODULE_USE_DRV_IMU_INV > 0)

#ifdef __cplusplus
extern "C"{
#endif

#define CMODULE_IMU_SPI (0U)

#define CMODULE_IMU_SPI_INST (SPI1)
#define CMODULE_IMU_SPI_PCSn (0)
#define CMODULE_IMU_SPI_CTARn (0)

#define CMODULE_IMU_I2C (1U)

#define CMODULE_IMU_I2C_INST (LPI2C1)


    
#if defined(CMODULE_IMU_SPI) && (CMODULE_IMU_SPI > 0)
    status_t DRVIMU_icm_example_spi_xfer(uint8_t* txbuf, uint8_t* rxbuf, uint32_t len);
#elif defined (CMODULE_IMU_I2C) && (CMODULE_IMU_I2C > 0)
    status_t DRVIMU_icm_example_i2c_rx(uint8_t slave_addr, uint8_t reg, uint8_t* buf, uint32_t len);
	status_t DRVIMU_icm_example_i2c_tx(uint8_t slave_addr, uint8_t reg, uint8_t* buf, uint32_t len);
	
#endif // ! CMODULE_IMU_SPI & CMODULE_IMU_I2C

#ifdef __cplusplus
}
#endif

#endif // CMODULE_USE_DRV_IMU_INV


#endif // ! D_MK66F18_DRV_IMU_PORT_H_
