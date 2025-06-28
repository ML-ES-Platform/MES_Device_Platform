#ifndef DD_LIGHTS_H
#define DD_LIGHTS_H

#include "Arduino.h"
#include "ed_relay/ed_relay.h"



#define DD_LIGHTS_ON    ED_RELAY_ON
#define DD_LIGHTS_OFF   ED_RELAY_OFF

#ifndef DD_LIGHTS_REC
#define DD_LIGHTS_REC (100) // Default lights cycle time in milliseconds
#endif

#ifndef DD_LIGHTS_OP_D_TIME
#define DD_LIGHTS_OP_D_TIME (1.0 * TIME_SEC)
#endif


void dd_lights_setup();
void dd_lights_loop();

int dd_lights_on(int time);
int dd_lights_off();
int dd_lights_get_state();
int dd_lights_set_state (int state);

#endif


