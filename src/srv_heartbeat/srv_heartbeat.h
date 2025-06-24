#ifndef SRV_HEARTBEAT_H
#define SRV_HEARTBEAT_H

//TODO: Rename tihis to srv_sys_heartbeat.h

#include "ecu_config.h"


// Include any necessary libraries here

// Define any constants or macros here
#ifndef SRV_HEARTBEAT_LED_PIN  
#define SRV_HEARTBEAT_LED_PIN -1 // GPIO8
#endif
// Declare any global variables here

// Declare any function prototypes here
void srv_heartbeat_setup();
void srv_heartbeat_loop();

#endif // SRV_HEARTBEAT_H
