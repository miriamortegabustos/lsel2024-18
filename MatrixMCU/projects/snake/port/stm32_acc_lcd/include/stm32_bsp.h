#ifndef __STM32_BSP_H
#define __STM32_BSP_H

#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_i2c.h"
#include "lsm303dlhc.h"

int stm32_i2c_init(void);

ACCELERO_DrvTypeDef *bsp_get_accelero(void);

uint16_t bsp_get_accelero_config(void);

void COMPASSACCELERO_IO_Write(uint16_t DeviceAddr, uint8_t RegisterAddr, uint8_t Value);

uint8_t COMPASSACCELERO_IO_Read(uint16_t DeviceAddr, uint8_t RegisterAddr);

#endif