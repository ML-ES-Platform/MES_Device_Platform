
#include <Arduino.h>
// #include "ecu_config.h"
// #include "ecu_modules.h"

#include "ctrl_can_steer/ctrl_can_steer.h"

void setup()
{
  void ctrl_can_steer_setup();
  
// #if defined(USE_SRV_SYS_OS_SEQ)
//   srv_sys_os_seq_setup();
// #elif defined(USE_SRV_SYS_OS_FREERTOS)
//   srv_sys_os_freertos_setup();
// #else
// #error "No OS defined"
// #endif
}

void loop()
{
  void ctrl_can_steer_loop();
  // Task Scheduler
// #if defined(USE_SRV_SYS_OS_SEQ)
//   // srv_sys_os_seq_scheduler();
// #elif defined(USE_SRV_OS_FREERTOS)
//   // nothing in the loop
// #else
//   #error "No OS defined"
//   srv_sys_os_seq_scheduler();
// #endif
//   // Ensuring a pause for recurrence
//   delay(SYS_TICK);
}

