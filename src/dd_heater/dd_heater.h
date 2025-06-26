#ifndef DD_HEATER_H
#define DD_HEATER_H

#include "ecu_config.h"



#define DD_HEATER_ON    ECU_STATUS_ON
#define DD_HEATER_OFF   ECU_STATUS_OFF

#ifndef DD_HEATER_REC
#define DD_HEATER_REC (100 ) // 100 ms
#endif

#ifndef DD_HEATER_OP_D_TIME
#define DD_HEATER_OP_D_TIME (1.0 * TIME_SEC / DD_HEATER_REC)
#endif

void dd_heater_setup();
void dd_heater_loop();

int dd_heater_on( int time);
int dd_heater_off();
int dd_heater_get_state();
int dd_heater_set_state (int state);

#endif


