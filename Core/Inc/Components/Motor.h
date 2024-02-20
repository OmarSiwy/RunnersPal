#ifndef __Motor_H
#define __Motor_H

#ifdef __cplusplus
extern "C" {
#endif

#include "Communication/hal.h"

typedef enum Orientation {
  FrontLeft,
  FrontRight,
  BackLeft,
  BackRight
} Orientation;

typedef struct MotorInterface {
  void (*Initialize)(Orientation);
  void (*ChangeSpeed)(Orientation, uint16_t);
  void (*StopMotor)(); 
} MotorInterface;

extern MotorInterface Motor;

#ifdef __cplusplus
}
#endif
#endif /* __Motor_H */
