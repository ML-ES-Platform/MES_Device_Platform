
#ifndef DD_JOYSTICK_H_
#define DD_JOYSTICK_H_



#include <Arduino.h>
#include "stdint.h"

#include "ecu_config.h"

// Joystick PinMap
#ifndef DD_JOYSTICK_X
#define DD_JOYSTICK_X A0
#endif
#ifndef DD_JOYSTICK_Y
#define DD_JOYSTICK_Y A3
#endif
#ifndef DD_JOYSTICK_B
#define DD_JOYSTICK_B 2
#endif


void dd_joystick_setup();
void dd_joystick_loop();
uint16_t dd_joystick_get_x();
uint16_t dd_joystick_get_y();
uint8_t dd_joystick_get_b();

void dd_joystick_report();

#endif
