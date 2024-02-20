#include "Components/IRSensor.h"

static void _Initialize(IRInterface Sensor) {
  GPIO_InitTypeDef GpioInit = {
    .Pin = Sensor.pin,
    .Mode = GPIO_MODE_INPUT,
    .Pull = GPIO_NOPULL,
  };
  HAL_GPIO_Init(Sensor.Group, &GpioInit);
}

static bool _CheckState(IRInterface Sensor) {
  return HAL_GPIO_ReadPin(Sensor.Group, Sensor.pin) == GPIO_PIN_SET ? true : false;
}

IRInterface IRSensor1 = {
  .Initialize = _Initialize,
  .CheckState = _CheckState,

  .Group = GPIOA,
  .pin = GPIO_PIN_0
};

IRInterface IRSensor2 = {
  .Initialize = _Initialize,
  .CheckState = _CheckState,

  .Group = GPIOA,
  .pin = GPIO_PIN_0
};
