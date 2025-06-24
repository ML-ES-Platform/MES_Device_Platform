#ifndef SRV_SYS_OS_FREERTOS_H
#define SRV_SYS_OS_FREERTOS_H

// Include any necessary libraries or headers
#include "ecu_config.h"

#include "srv_sys_os.h"

#ifdef ESP32
// #include <FreeRTOS.h>
#else
#include <Arduino_FreeRTOS.h>
#endif
// Define any constants or macros


// Declare any global variables or data structures

// Declare function prototypes
void srv_sys_os_freertos_setup();
void srv_sys_os_freertos_scheduler();

#endif // SRV_SYS_OS_FREERTOS_H
