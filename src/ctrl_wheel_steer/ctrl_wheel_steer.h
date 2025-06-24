#ifndef CTRL_WHEEL_STEER_H
#define CTRL_WHEEL_STEER_H
#include "ecu_config.h"

// Include any necessary headers here

// Define any constants or macros here

#define CTRL_WHEEL_STEER_TARGET_MODE_CAN 0
#define CTRL_WHEEL_STEER_TARGET_MODE_BT 1
#define CTRL_WHEEL_STEER_TARGET_MODE_MANUAL 2

#ifndef CTRL_WHEEL_STEER_TARGET_MODE
#define CTRL_WHEEL_STEER_TARGET_MODE CTRL_WHEEL_STEER_TARGET_MODE_MANUAL
#endif

#define CTRL_WHEEL_STEER_FB_MODE_ENCODER 0
#define CTRL_WHEEL_STEER_FB_MODE_POTENTIOMETER 1
#define CTRL_WHEEL_STEER_FB_MODE_TIMER 2

#ifndef CTRL_WHEEL_STEER_FB_MODE
#define CTRL_WHEEL_STEER_FB_MODE CTRL_WHEEL_STEER_FB_MODE_TIMER
#endif

#define CTRL_WHEEL_STEER_OP_MODE_STEP 0
#define CTRL_WHEEL_STEER_OP_MODE_CONTINUOUS 1
#define CTRL_WHEEL_STEER_OP_MODE_POWER 2

#ifndef CTRL_WHEEL_STEER_OP_MODE
#define CTRL_WHEEL_STEER_OP_MODE CTRL_WHEEL_STEER_OP_MODE_STEP
#endif

#define CTRL_WHEEL_STEER_DISABLE 0
#define CTRL_WHEEL_STEER_ENABLE 1

#ifndef CTRL_WHEEL_STEER_MODE
#define CTRL_WHEEL_STEER_MODE CTRL_WHEEL_STEER_ENABLE
#endif

#ifndef CTRL_WHEEL_STEER_POWER
#define CTRL_WHEEL_STEER_POWER 255
#endif

// Declare any function prototypes here

int8_t ctrl_wheel_steer_enable();
int8_t ctrl_wheel_steer_disable();
int8_t ctrl_wheel_steer_is_enabled();
uint8_t ctrl_wheel_steer_set_target_mode(uint8_t mode);
uint8_t ctrl_wheel_steer_get_target_mode();
uint8_t ctrl_wheel_steer_set_fb_mode(uint8_t mode);
uint8_t ctrl_wheel_steer_get_fb_mode();

int16_t ctrl_wheel_steer_get_power();
int16_t ctrl_wheel_steer_set_power(int16_t power);
int16_t ctrl_wheel_steer_power_up(int16_t power);
int16_t ctrl_wheel_steer_power_down(int16_t power);

int16_t ctrl_wheel_steer_get_target_angle();
int16_t ctrl_wheel_steer_set_target_angle(int16_t angle);
int16_t ctrl_wheel_steer_get_current_angle();
int16_t ctrl_wheel_steer_set_current_angle(int16_t angle);

int16_t ctrl_wheel_steer_turn_right(int16_t angle);
int16_t ctrl_wheel_steer_turn_left(int16_t angle);

void ctrl_wheel_steer_setup();
void ctrl_wheel_steer_loop();

#endif // CTRL_WHEEL_STEER_H
