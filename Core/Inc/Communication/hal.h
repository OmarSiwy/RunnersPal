#ifndef __HAL_H
#define __HAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "Communication/usart.h"
#include "Communication/adc.h"
#include "Communication/i2c.h"
#include "Communication/spi.h"
#include "Communication/tim.h"
#include "Communication/gpio.h"

#include <stdint.h>
#include <stdbool.h>

// Testing Framework Setup
#define Testing

#ifdef Testing
#define getName(var) #var // To Trace out Variable Names
// GPIO
#define GPIOWrite(PortGroup, PortName, ON_OFF) \
    printf("%s, %s, has been turned %s\n", getName(PortGroup), getName(PortName), getName(ON_OFF))
#define GPIORead(PortGroup, PortName) \
    printf("%s, %s, has been read", getName(PortGroup), getName(PortName))
// I2C
#define I2CRead(I2C, DevAddr, MemAddress, MemAddSize, pData, Size, Timeout) \
    printf("I2C Mem Read from device address %s, memory address %s, size %s\n", getName(DevAddr), getName(MemAddress), getName(Size))

#define I2CWrite(I2C, DevAddr, MemAddress, MemAddSize, pData, Size, Timeout) \
    printf("I2C Mem Write to device address %s, memory address %s, size %s\n", getName(DevAddr), getName(MemAddress), getName(Size))

#else 
// GPIO
#define GPIORead(PortGroup, PortName) \
  HAL_GPIO_WritePin((GPIO_TypeDef*)PortGroup, (uint16_t)PortName)
#define GPIOWrite(PortGroup, PortName, ON_OFF) \
  HAL_GPIO_WritePin((GPIO_TypeDef*)PortGroup, (uint16_t)PortName, (enum)ON_OFF)
// I2C
#define I2CRead(I2C, DevAddr, MemAddress, MemAddSize, pData, Size, Timeout) \
    HAL_I2C_Mem_Read(I2C, DevAddr, MemAddress, MemAddSize, pData, Size, Timeout)

#define I2CWrite(I2C, DevAddr, MemAddress, MemAddSize, pData, Size, Timeout) \
    HAL_I2C_Mem_Write(I2C, DevAddr, MemAddress, MemAddSize, pData, Size, Timeout)
#endif


#ifdef __cplusplus
}
#endif
#endif /* __HAL_H */
