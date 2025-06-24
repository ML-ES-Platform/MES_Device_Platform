#ifndef CTRL_WHEEL_TRACT_H
#define CTRL_WHEEL_TRACT_H
#include "ecu_config.h"
// Include any necessary headers here

// Define any constants or macros here

#define CTRL_WHEEL_TRACT_TARGET_MODE_CAN 0
#define CTRL_WHEEL_TRACT_TARGET_MODE_BT 1
#define CTRL_WHEEL_TRACT_TARGET_MODE_MANUAL 2

#ifndef CTRL_WHEEL_TRACT_TARGET_MODE
#define CTRL_WHEEL_TRACT_TARGET_MODE CTRL_WHEEL_TRACT_TARGET_MODE_MANUAL
#endif

#define CTRL_WHEEL_TRACT_FB_MODE_ENCODER 0
#define CTRL_WHEEL_TRACT_FB_MODE_POTENTIOMETER 1
#define CTRL_WHEEL_TRACT_FB_MODE_TIMER 2

#ifndef CTRL_WHEEL_TRACT_FB_MODE
#define CTRL_WHEEL_TRACT_FB_MODE CTRL_WHEEL_TRACT_FB_MODE_TIMER
#endif


#define CTRL_WHEEL_TRACT_OP_MODE_STEP 0
#define CTRL_WHEEL_TRACT_OP_MODE_CONTINUOUS 1
#define CTRL_WHEEL_TRACT_OP_MODE_POWER 2

#ifndef CTRL_WHEEL_TRACT_OP_MODE
#define CTRL_WHEEL_TRACT_OP_MODE CTRL_WHEEL_TRACT_OP_MODE_POWER
#endif

#define CTRL_WHEEL_TRACT_DISABLE 0
#define CTRL_WHEEL_TRACT_ENABLE 1

#ifndef CTRL_WHEEL_TRACT_MODE
#define CTRL_WHEEL_TRACT_MODE CTRL_WHEEL_TRACT_ENABLE
#endif

#ifndef CTRL_WHEEL_TRACT_POWER
#define CTRL_WHEEL_TRACT_POWER 255
#endif

// Declare any function prototypes here

int8_t ctrl_wheel_tract_enable();
int8_t ctrl_wheel_tract_disable();
int8_t ctrl_wheel_tract_is_enabled();
uint8_t ctrl_wheel_tract_set_target_mode(uint8_t mode);
uint8_t ctrl_wheel_tract_get_target_mode();
uint8_t ctrl_wheel_tract_set_fb_mode(uint8_t mode);
uint8_t ctrl_wheel_tract_get_fb_mode();
uint8_t ctrl_wheel_tract_set_op_mode(uint8_t mode);
uint8_t ctrl_wheel_tract_get_op_mode();
uint8_t ctrl_wheel_tract_is_step_mode();




int16_t ctrl_wheel_tract_get_power();
int16_t ctrl_wheel_tract_set_power(int16_t power);
int16_t ctrl_wheel_tract_power_up(int16_t power);
int16_t ctrl_wheel_tract_power_down(int16_t power);

int16_t ctrl_wheel_tract_get_target_step();
int16_t ctrl_wheel_tract_set_target_step(int16_t step);
int16_t ctrl_wheel_tract_get_current_step();
int16_t ctrl_wheel_tract_set_current_step(int16_t step);

int16_t ctrl_wheel_tract_step_up(int16_t step);
int16_t ctrl_wheel_tract_step_down(int16_t step);

void ctrl_wheel_tract_setup();
void ctrl_wheel_tract_loop();


#endif // CTRL_WHEEL_TRACT_H
