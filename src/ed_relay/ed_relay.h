#ifndef ED_RELAY_H
#define ED_RELAY_H

#include "Arduino.h"
#include "ecu_config.h"

#ifndef ED_RELAY_1_PIN
#define ED_RELAY_1_PIN -1 //GPIO1
#endif
#ifndef ED_RELAY_2_PIN
#define ED_RELAY_2_PIN -1 //GPIO2
#endif
#ifndef ED_RELAY_3_PIN
#define ED_RELAY_3_PIN -1 // GPIO3
#endif
#ifndef ED_RELAY_4_PIN
#define ED_RELAY_4_PIN -1 // GPIO4
#endif
#ifndef ED_RELAY_5_PIN
#define ED_RELAY_5_PIN -1 // GPIO5
#endif
#ifndef ED_RELAY_6_PIN  
#define ED_RELAY_6_PIN -1 // GPIO6
#endif
#ifndef ED_RELAY_7_PIN
#define ED_RELAY_7_PIN -1 // GPIO7
#endif
#ifndef ED_RELAY_8_PIN  
#define ED_RELAY_8_PIN -1 // GPIO8
#endif

#define ED_RELAY_ON LOW
#define ED_RELAY_OFF HIGH



enum ed_relay_t{
    ED_RELAY_WIN_POS_TERM_ID,
    ED_RELAY_WIN_NEG_TERM_ID,
    ED_RELAY_HEAT_ID,
    ED_RELAY_HUMIDIFY_ID,
    ED_RELAY_MOIST_ID,
    ED_RELAY_AIR_PUMP_ID,
    ED_RELAY_LIGHTS_ID,
    ED_RELAY_ID_8,
    ED_RELAY_NR_OF
};

void ed_relay_setup();
void ed_relay_loop();

int ed_relay_on(size_t relay_it);
int ed_relay_off(size_t relay_it);
int ed_relay_getState(size_t relay_it);
int ed_relay_setState (size_t relay_it, int state);
int ed_relay_get_pin(size_t relay_it);

#endif


