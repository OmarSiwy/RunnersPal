/**
  ******************************************************************************
  * @file    stm32f4xx_it.c
  * @brief   Interrupt Service Routines.
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

#include "main.h"
#include "stm32f4xx_it.h"

/* External variables --------------------------------------------------------*/
extern ADC_HandleTypeDef hadc1;
extern I2C_HandleTypeDef hi2c1;
extern SPI_HandleTypeDef hspi1;
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim5;
extern UART_HandleTypeDef huart2;
extern TIM_HandleTypeDef htim9;

/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void) {
   while (1) {}
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void) {
  while (1) {}
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void) {
  while (1) {}
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void) {
  while (1) {}
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void) {
  while (1) {}
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void) {
  
}

/******************************************************************************/
/* STM32F4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f4xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles PVD interrupt through EXTI line 16.
  */
void PVD_IRQHandler(void) {
  HAL_PWR_PVD_IRQHandler();
}

/**
  * @brief This function handles Flash global interrupt.
  */
void FLASH_IRQHandler(void) {
  HAL_FLASH_IRQHandler();
}

/**
  * @brief This function handles RCC global interrupt.
  */
void RCC_IRQHandler(void) {
}

/**
  * @brief This function handles ADC1 global interrupt.
  */
void ADC_IRQHandler(void) {
  HAL_ADC_IRQHandler(&hadc1);
}

/**
  * @brief This function handles TIM1 break interrupt and TIM9 global interrupt.
  */
void TIM1_BRK_TIM9_IRQHandler(void) {
  HAL_TIM_IRQHandler(&htim1);
  HAL_TIM_IRQHandler(&htim9);
}

/**
  * @brief This function handles TIM2 global interrupt.
  */
void TIM2_IRQHandler(void) {
  HAL_TIM_IRQHandler(&htim2);
}

/**
  * @brief This function handles TIM3 global interrupt.
  */
void TIM3_IRQHandler(void) {
  HAL_TIM_IRQHandler(&htim3);
}

/**
  * @brief This function handles TIM4 global interrupt.
  */
void TIM4_IRQHandler(void) {
  HAL_TIM_IRQHandler(&htim4);
}

/**
  * @brief This function handles I2C1 event interrupt.
  */
void I2C1_EV_IRQHandler(void) {
  HAL_I2C_EV_IRQHandler(&hi2c1);
}

/**
  * @brief This function handles I2C1 error interrupt.
  */
void I2C1_ER_IRQHandler(void) {
  HAL_I2C_ER_IRQHandler(&hi2c1);
}

/**
  * @brief This function handles SPI1 global interrupt.
  */
void SPI1_IRQHandler(void) {
  HAL_SPI_IRQHandler(&hspi1);
}

/**
  * @brief This function handles USART2 global interrupt.
  */
void USART2_IRQHandler(void) {
  HAL_UART_IRQHandler(&huart2);
}

/**
  * @brief This function handles TIM5 global interrupt.
  */
void TIM5_IRQHandler(void) {
  HAL_TIM_IRQHandler(&htim5);
}
