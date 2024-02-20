#include "Communication/tim.h"

TIM_HandleTypeDef htim1; // CAN NOT PWM
TIM_HandleTypeDef htim2; 
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;
TIM_HandleTypeDef htim5;

void SetupTIMHandle(TIM_HandleTypeDef *handle, TIM_TypeDef *Instance, bool PWM) {
  handle->Instance = Instance;
  uint32_t Period = 999; // 16-bit timers
  handle->Init.Period = Period;
  handle->Init.Prescaler = 71;
  handle->Init.CounterMode = TIM_COUNTERMODE_UP;
  handle->Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  if (!PWM) handle->Init.RepetitionCounter = 0;
  handle->Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;

  if (HAL_TIM_Base_Init(handle) != HAL_OK) Error_Handler();

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(handle, &sClockSourceConfig) != HAL_OK) Error_Handler();

  if (PWM) {
    if (HAL_TIM_PWM_Init(handle) != HAL_OK) Error_Handler();

    TIM_OC_InitTypeDef sConfigOC = {0};
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = Period / 2; // 50% duty cycle
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    if (HAL_TIM_PWM_ConfigChannel(handle, &sConfigOC, TIM_CHANNEL_1) != HAL_OK) Error_Handler();
  }

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(handle, &sMasterConfig) != HAL_OK) Error_Handler();

  // Post-initialization
  HAL_TIM_Base_MspInit(handle);
  if (PWM) {
    HAL_TIM_MspPostInit(handle);
    if (HAL_TIM_PWM_Start(handle, TIM_CHANNEL_1) != HAL_OK) Error_Handler();
  }
}


void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* tim_baseHandle) {
  if(tim_baseHandle->Instance==TIM1) {
    /* TIM1 clock enable */
    __HAL_RCC_TIM1_CLK_ENABLE();
    /* TIM1 interrupt Init */
    HAL_NVIC_SetPriority(TIM1_BRK_TIM9_IRQn, 15, 0);
    HAL_NVIC_EnableIRQ(TIM1_BRK_TIM9_IRQn);
  }
  else if(tim_baseHandle->Instance==TIM2) {
    /* TIM2 clock enable */
    __HAL_RCC_TIM2_CLK_ENABLE();

    /* TIM2 interrupt Init */
    //HAL_NVIC_SetPriority(TIM2_IRQn, 5, 0);
    //HAL_NVIC_EnableIRQ(TIM2_IRQn);
  }
  else if(tim_baseHandle->Instance==TIM3) {
    /* TIM3 clock enable */
    __HAL_RCC_TIM3_CLK_ENABLE();

    /* TIM3 interrupt Init */
    //HAL_NVIC_SetPriority(TIM3_IRQn, 5, 0);
    //HAL_NVIC_EnableIRQ(TIM3_IRQn);
  }
  else if(tim_baseHandle->Instance==TIM4) {
    /* TIM4 clock enable */
    __HAL_RCC_TIM4_CLK_ENABLE();

    /* TIM4 interrupt Init */
    //HAL_NVIC_SetPriority(TIM4_IRQn, 5, 0);
    //HAL_NVIC_EnableIRQ(TIM4_IRQn);
  }
  else if(tim_baseHandle->Instance==TIM5) {
    /* TIM5 clock enable */
    __HAL_RCC_TIM5_CLK_ENABLE();

    /* TIM5 interrupt Init */
    //HAL_NVIC_SetPriority(TIM5_IRQn, 5, 0);
    //HAL_NVIC_EnableIRQ(TIM5_IRQn);
  }
}
void HAL_TIM_MspPostInit(TIM_HandleTypeDef* timHandle) {
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(timHandle->Instance==TIM2) {
    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**TIM2 GPIO Configuration
    PA5     ------> TIM2_CH1
    */
    GPIO_InitStruct.Pin = GPIO_PIN_5;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF1_TIM2;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
  }
  else if(timHandle->Instance==TIM3) {
    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**TIM3 GPIO Configuration
    PA6     ------> TIM3_CH1
    */
    GPIO_InitStruct.Pin = GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF2_TIM3;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
  }
  else if(timHandle->Instance==TIM4) {
    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**TIM4 GPIO Configuration
    PB6     ------> TIM4_CH1
    */
    GPIO_InitStruct.Pin = GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF2_TIM4;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
  }
  else if(timHandle->Instance==TIM5) {
    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**TIM5 GPIO Configuration
    PA0-WKUP     ------> TIM5_CH1
    */
    GPIO_InitStruct.Pin = GPIO_PIN_0;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF2_TIM5;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
  }
}

void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* tim_baseHandle) {
  if(tim_baseHandle->Instance==TIM1) {
    /* Peripheral clock disable */
    __HAL_RCC_TIM1_CLK_DISABLE();

    /* TIM1 interrupt Deinit */
    //HAL_NVIC_DisableIRQ(TIM1_BRK_TIM9_IRQn);
  }
  else if(tim_baseHandle->Instance==TIM2) {
    /* Peripheral clock disable */
    __HAL_RCC_TIM2_CLK_DISABLE();

    /* TIM2 interrupt Deinit */
    //HAL_NVIC_DisableIRQ(TIM2_IRQn);
  }
  else if(tim_baseHandle->Instance==TIM3) {
    /* Peripheral clock disable */
    __HAL_RCC_TIM3_CLK_DISABLE();

    /* TIM3 interrupt Deinit */
    //HAL_NVIC_DisableIRQ(TIM3_IRQn);
  }
  else if(tim_baseHandle->Instance==TIM4) {
    /* Peripheral clock disable */
    __HAL_RCC_TIM4_CLK_DISABLE();

    /* TIM4 interrupt Deinit */
    //HAL_NVIC_DisableIRQ(TIM4_IRQn);
  }
  else if(tim_baseHandle->Instance==TIM5) {
    /* Peripheral clock disable */
    __HAL_RCC_TIM5_CLK_DISABLE();

    /* TIM5 interrupt Deinit */
    //HAL_NVIC_DisableIRQ(TIM5_IRQn);
  }
}
