#ifndef __IRSENSOR_H
#define __IRSENSOR_H

#ifdef __cplusplus
extern "C" {
#endif

#include "Communication/hal.h"

typedef struct IRInterface {
  void (*Initialize)(IRInterface);
  bool (*CheckState)(IRInterface); 

  GPIO_TypeDef* Group;
  uint16_t pin;
} IRInterface;

extern IRInterface IRSensor1;
extern IRINterface IRSensor2;

#ifdef __cplusplus
}
#endif
#endif /* __IRSENSOR_H */
