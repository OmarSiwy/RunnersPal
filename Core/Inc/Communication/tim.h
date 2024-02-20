/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    tim.h
  * @brief   This file contains all the function prototypes for
  *          the tim.c file
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
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TIM_H__
#define __TIM_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include <stdbool.h>

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim5;

/*
 *
 * Duty Cycle = Time On / Total Time x 100
 * Resolution = 2^(Numbers of Bits) discrete levels
 * Frequency = Clock Frequency / ((Prescaler + 1) x (Internal Clock Period + 1))
 * @param
 */
void SetupTIMHandle(TIM_HandleTypeDef *handle, TIM_TypeDef *Instance, bool PWM);

// To Start PWM:
// HAL_TIM_PWM_Start();
// To Start Clock:
// HAL_TIM_Base_Start();

// Generated
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* tim_baseHandle);
void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);
void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* tim_baseHandle);

#ifdef __cplusplus
}
#endif

#endif /* __TIM_H__ */

