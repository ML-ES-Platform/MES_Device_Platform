#ifndef CTRL_AMB_LIGHT_H_
#define CTRL_AMB_LIGHT_H_

#include "ecu_config.h"

#include "stdint.h"

#define CTRL_AMB_LIGHT_DISABLE 0
#define CTRL_AMB_LIGHT_ENABLE 1

#ifndef CTRL_AMB_LIGHT_SP_DEFAULT
#define CTRL_AMB_LIGHT_SP_DEFAULT (60.0)
#endif

#ifndef CTRL_AMB_LIGHT_HISTERESIS
#define CTRL_AMB_LIGHT_HISTERESIS (5.0)
#endif

#ifndef CTRL_AMB_LIGHT_OP_D_TIME
#define CTRL_AMB_LIGHT_OP_D_TIME (1.0 * TIME_SEC)
#endif

#define CTRL_AMB_LIGHT_OUT_OFF 0
#define CTRL_AMB_LIGHT_OUT_ON 1


void ctrl_amb_light_setup();
void ctrl_amb_light_loop();

int8_t ctrl_amb_light_set_mode(int8_t mode);
int8_t ctrl_amb_light_set_mode_manual();
int8_t ctrl_amb_light_set_mode_auto();
int8_t ctrl_amb_light_get_mode();
int8_t ctrl_amb_light_is_enabled();

float ctrl_amb_light_get_current_light();
float ctrl_amb_light_set_setpoint(float setpoint);
float ctrl_amb_light_get_setpoint();
float ctrl_amb_light_setpoint_up(float d_val);
float ctrl_amb_light_setpoint_dn(float d_val);
int8_t ctrl_amb_light_get_output();

#endif
