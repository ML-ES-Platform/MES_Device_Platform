#ifndef CTRL_AIR_TEMP_VENT_H_
#define CTRL_AIR_TEMP_VENT_H_
#include "ecu_config.h"

#include "stdint.h"

#ifndef CTRL_AIR_TEMP_VENT_HISTERESIS
#define CTRL_AIR_TEMP_VENT_HISTERESIS (0.5)
#endif

#ifndef CTRL_AIR_TEMP_VENT_OP_D_TIME
#define CTRL_AIR_TEMP_VENT_OP_D_TIME (1.0 * TIME_SEC)
#endif

#ifndef CTRL_AIR_TEMP_VENT_SP_DEFAULT
#define CTRL_AIR_TEMP_VENT_SP_DEFAULT (19.0)
#endif

#define CTRL_AIR_TEMP_VENT_DISABLE 0
#define CTRL_AIR_TEMP_VENT_ENABLE 1

enum ctrl_air_temp_vent_out_state_t{
    CTRL_AIR_TEMP_VENT_OUT_STOP,
    CTRL_AIR_TEMP_VENT_OUT_CLOSE,
    CTRL_AIR_TEMP_VENT_OUT_OPEN,
    CTRL_AIR_TEMP_VENT_OUT_UNKNOWN = -1
};


void ctrl_air_temp_vent_setup();
void ctrl_air_temp_vent_loop();

int8_t ctrl_air_temp_vent_set_mode(int8_t mode);
int8_t ctrl_air_temp_vent_set_mode_manual();
int8_t ctrl_air_temp_vent_set_mode_auto();
int8_t ctrl_air_temp_vent_get_mode();
int8_t ctrl_air_temp_vent_is_enabled();

float ctrl_air_temp_vent_get_current_temp();
float ctrl_air_temp_vent_set_setpoint(float setpoint);
float ctrl_air_temp_vent_get_setpoint();
float ctrl_air_temp_vent_setpoint_up(float d_val);
float ctrl_air_temp_vent_setpoint_dn(float d_val);
int8_t ctrl_air_temp_vent_get_output();

#endif
