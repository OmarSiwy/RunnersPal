#include "Communication/gpio.h"

/*
 * Always Call this in the Start of the Program, for Power Saving
 */
void MX_GPIO_Init(void) {
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  // Enable all GPIO clocks
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE(); 

  // Configure all pins in analog mode with no pull-up or pull-down resistors
  GPIO_InitStruct.Pin = GPIO_PIN_All; 
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  
  // Apply configuration to all GPIO ports
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
  HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);
}

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void SetupGPIOHandle(GPIOCONFIG *GPIOARR, size_t size) {
  for (int i = 0; i < size; i++) {
    // ONLY FOR OUTPUT PINS
    if (GPIOARR[i].Init.Mode == GPIO_MODE_OUTPUT_PP)
      HAL_GPIO_WritePin(GPIOARR[i].port, GPIOARR[i].Init.Pin, GPIO_PIN_RESET);

    HAL_GPIO_Init(GPIOARR[i].port, &GPIOARR[i].Init);
  }
}
