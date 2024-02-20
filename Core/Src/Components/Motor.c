#include "Components/Motor.h"

static TIM_HandleTypeDef* GetMotor(Orientation orientation) {
  switch(orientation) {
    case FrontLeft:
      return &htim2;
    case FrontRight:
      return &htim3;
    case BackLeft:
      return &htim4;
    case BackRight:
      return &htim5;
  }
}

static void InitializeMotor(Orientation orientation) {
  switch(orientation) {
    case FrontLeft:
      SetupTIMHandle(&htim2, TIM2, true);
      break;
    case FrontRight:
      SetupTIMHandle(&htim3, TIM3, true);
      break;
    case BackLeft:
      SetupTIMHandle(&htim4, TIM4, true);
      break;
    case BackRight:
      SetupTIMHandle(&htim5, TIM5, true);
      break;
  } 
}

static void _StopMotor(Orientation orientation) {
  if (HAL_TIM_PWM_Stop(GetMotor(orientation), TIM_CHANNEL_1) != HAL_OK) Error_Handler();
}

static void _ChangeSpeed(Orientation orientation, uint16_t speedPercent) {
  if (speedPercent > 100) speedPercent = 100;

  TIM_HandleTypeDef* MotorController = GetMotor(orientation);

  int Pulse = ((double)(speedPercent)/100)*(MotorController->Init.Period);
  __HAL_TIM_SET_COMPARE(MotorController, TIM_CHANNEL_1, Pulse);
}

MotorInterface Motor = {
  .Initialize = InitializeMotor,
  .ChangeSpeed = _ChangeSpeed,
  .StopMotor = _StopMotor
};
