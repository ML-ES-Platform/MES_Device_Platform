
#include <Arduino.h>
#include "ecu_config.h"
#include "ecu_modules.h"

void setup()
{

#if defined(USE_SRV_SYS_OS_SEQ)
  srv_sys_os_seq_setup();
#elif defined(USE_SRV_SYS_OS_FREERTOS)
  srv_sys_os_freertos_setup();
#else
#error "No OS defined"
#endif
}

void loop()
{
  // Task Scheduler
#if defined(USE_SRV_SYS_OS_SEQ)
  // srv_sys_os_seq_scheduler();
#elif defined(USE_SRV_OS_FREERTOS)
  // nothing in the loop
#else
// #error "No OS defined"
#endif
  // Ensuring a pause for recurrence
  delay(SYS_TICK);
}
