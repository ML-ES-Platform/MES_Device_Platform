#ifndef DD_VALVE_H
#define DD_VALVE_H

#include "ed_relay/ed_relay.h"

#define DD_VALVE_OPEN    ED_RELAY_ON
#define DD_VALVE_CLOSE   ED_RELAY_OFF

#ifndef DD_VALVE_REC
#define DD_VALVE_REC (100) // Default valve cycle time in milliseconds
#endif

#ifndef DD_VALVE_OP_D_TIME
#define DD_VALVE_OP_D_TIME (1.0 * TIME_SEC)
#endif


enum dd_valve_t {
    DD_VALVE_AIR_HUM_ID,
    DD_VALVE_SOIL_MOIST_ID,
    DD_VALVE_NR_OF
};

void dd_valve_setup();
void dd_valve_loop();

int dd_valve_on(size_t valve_it ,int time);
int dd_valve_off(size_t valve_it);
int dd_valve_get_state(size_t valve_it);
int dd_valve_set_state(size_t valve_it, int state);

#endif


