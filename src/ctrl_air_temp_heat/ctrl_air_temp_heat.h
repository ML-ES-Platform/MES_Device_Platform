#ifndef CTRL_AIR_TEMP_HEAT_H_
#define CTRL_AIR_TEMP_HEAT_H_
#include "ecu_config.h"

#include "stdint.h"

#define CTRL_AIR_TEMP_HEAT_DISABLE 0
#define CTRL_AIR_TEMP_HEAT_ENABLE 1

#ifndef CTRL_AIR_TEMP_HEAT_SP_DEFAULT
#define CTRL_AIR_TEMP_HEAT_SP_DEFAULT (19.0)
#endif

#ifndef CTRL_AIR_TEMP_HEAT_HISTERESIS
#define CTRL_AIR_TEMP_HEAT_HISTERESIS (0.5)
#endif

#ifndef CTRL_AIR_TEMP_HEAT_OP_D_TIME
#define CTRL_AIR_TEMP_HEAT_OP_D_TIME (1.0 * TIME_SEC)
#endif

#define CTRL_AIR_TEMP_HEAT_OUT_OFF 0
#define CTRL_AIR_TEMP_HEAT_OUT_ON 1


void ctrl_air_temp_heat_setup();
void ctrl_air_temp_heat_loop();

int8_t ctrl_air_temp_heat_set_mode(int8_t mode);
int8_t ctrl_air_temp_heat_set_mode_manual();
int8_t ctrl_air_temp_heat_set_mode_auto();
int8_t ctrl_air_temp_heat_get_mode();
int8_t ctrl_air_temp_heat_is_enabled();

float ctrl_air_temp_heat_get_current_temp();
float ctrl_air_temp_heat_set_setpoint(float setpoint);
float ctrl_air_temp_heat_get_setpoint();
float ctrl_air_temp_heat_setpoint_up(float d_val);
float ctrl_air_temp_heat_setpoint_dn(float d_val);
int8_t ctrl_air_temp_heat_get_output();

#endif
