

#include "stm32_bsp.h"
I2C_HandleTypeDef hi2c1; //Variable para la estructura del I2C

ACCELERO_DrvTypeDef *bsp_get_accelero() {
return &Lsm303dlhcDrv;
}

int stm32_i2c_init(){

    hi2c1.Instance = I2C1;
    hi2c1.Init.ClockSpeed = 100000;
    hi2c1.Init.DutyCycle = 0;
    hi2c1.Init.OwnAddress1 = 0;
    hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    hi2c1.Init.DualAddressMode = 0;
    hi2c1.Init.OwnAddress2 = 0;
    hi2c1.Init.GeneralCallMode = 0;
    hi2c1.Init.NoStretchMode = 0;
    if (HAL_I2C_Init(&hi2c1) != HAL_OK)
    {
         return 0;
    }

    return 1;

}

uint16_t bsp_get_accelero_config() {
    ACCELERO_InitTypeDef acc_init_config;
    uint16_t ctrl=0;;

    acc_init_config.Power_Mode = LSM303DLHC_NORMAL_MODE;
    acc_init_config.AccOutput_DataRate = LSM303DLHC_ODR_50_HZ;
    acc_init_config.Axes_Enable = LSM303DLHC_AXES_ENABLE;
    acc_init_config.AccFull_Scale = LSM303DLHC_FULLSCALE_2G;
    acc_init_config.BlockData_Update = LSM303DLHC_BlockUpdate_Continous;
    acc_init_config.Endianness = LSM303DLHC_BLE_LSB;
    acc_init_config.High_Resolution = LSM303DLHC_HR_ENABLE;
    ctrl |= (acc_init_config.Power_Mode | \
    acc_init_config.AccOutput_DataRate | \
    acc_init_config.Axes_Enable);
    ctrl |= ((acc_init_config.BlockData_Update | acc_init_config.Endianness | \
    acc_init_config.AccFull_Scale | acc_init_config.High_Resolution) << 8);

    return ctrl;
}

void COMPASSACCELERO_IO_Init(void){
    
    stm32_i2c_init();
}


void COMPASSACCELERO_IO_Write(uint16_t DeviceAddr, uint8_t RegisterAddr, uint8_t Value){

    HAL_I2C_Mem_Write(&hi2c1, DeviceAddr, RegisterAddr, I2C_MEMADD_SIZE_8BIT, &Value, 1, 1000);

}

uint8_t COMPASSACCELERO_IO_Read(uint16_t DeviceAddr, uint8_t RegisterAddr){

    uint8_t pData =0;
    //HAL_I2C_Master_Receive(&hi2c1, DeviceAddr, &pData, I2C_MEMADD_SIZE_8BIT,  1000);
    HAL_I2C_Mem_Read(&hi2c1,  DeviceAddr,  RegisterAddr,  I2C_MEMADD_SIZE_8BIT, &pData, 1, 1000);

    return pData;
}