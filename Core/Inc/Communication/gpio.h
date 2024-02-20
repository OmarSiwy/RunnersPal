/**
  ******************************************************************************
  * @file    gpio.h
  * @brief   This file contains all the function prototypes for
  *          the gpio.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
#ifndef __GPIO_H__
#define __GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

typedef struct GPIOCONFIG {
  GPIO_InitTypeDef Init;
  GPIO_TypeDef* port;
} GPIOCONFIG;

void MX_GPIO_Init(void);
void SetupGPIOHandle(GPIOCONFIG* GPIOARR, size_t size);

#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */

