#ifndef DD_WATER_PUMP_H
#define DD_WATER_PUMP_H

#include "Arduino.h"
#include "ed_relay/ed_relay.h"



#define DD_WATER_PUMP_ON    ED_RELAY_ON
#define DD_WATER_PUMP_OFF   ED_RELAY_OFF

#ifndef DD_WATER_PUMP_REC
#define DD_WATER_PUMP_REC (100)
#endif

#ifndef DD_WATER_PUMP_OP_D_TIME
#define DD_WATER_PUMP_OP_D_TIME (1.0 * TIME_SEC)
#endif



void dd_water_pump_setup();
void dd_water_pump_loop();

int dd_water_pump_on(int time);
int dd_water_pump_off();
int dd_water_pump_get_state();
int dd_water_pump_set_state(int state);

#endif


