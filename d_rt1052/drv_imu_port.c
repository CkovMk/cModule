#include "drv_imu_port.h"

#if defined(CMODULE_USE_DRV_IMU_INV) && (CMODULE_USE_DRV_IMU_INV > 0)

#ifdef __cplusplus
extern "C"{
#endif

#if defined(CMODULE_IMU_SPI) && (CMODULE_IMU_SPI > 0)
    status_t DRVIMU_icm_example_spi_xfer(uint8_t* txbuf, uint8_t* rxbuf, uint32_t len)
	{
		return 1;
	}
#elif defined (CMODULE_IMU_I2C) && (CMODULE_IMU_I2C > 0)
    status_t DRVIMU_icm_example_i2c_rx(uint8_t slave_addr, uint8_t reg, uint8_t* buf, uint32_t len)
	{
		return HAL_I2C_Mem_ReadBlocking(CMODULE_IMU_I2C_INST, slave_addr, reg, 1, buf, len);
	}
	
	status_t DRVIMU_icm_example_i2c_tx(uint8_t slave_addr, uint8_t reg, uint8_t* buf, uint32_t len)
	{
		return HAL_I2C_Mem_WriteBlocking(CMODULE_IMU_I2C_INST, slave_addr, reg, 1, buf, len);
	}
	
#endif // CMODULE_IMU_SPI

#ifdef __cplusplus
}
#endif

#endif // CMODULE_USE_DRV_IMU_INV
