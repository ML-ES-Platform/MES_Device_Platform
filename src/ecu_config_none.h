#ifndef ECU_CONFIG_NONE_H_
#define ECU_CONFIG_NONE_H_

// #define USE_SRV_SYS_OS_SEQ
#define USE_SRV_SYS_OS_FREERTOS
#define USE_SRV_UI_SERIAL



#define USE_SRV_HEARTBEAT

//-------------------------------------------------------------------------
// configure task recurrence and offset for services
#define SRV_UI_SERIAL_IN_REC (1 * TIME_mSEC)
#define SRV_UI_SERIAL_IN_OFFSET (4 * TIME_mSEC)

#define SRV_UI_SERIAL_OUT_REC (5.0 * TIME_SEC)
#define SRV_UI_SERIAL_OUT_OFFSET (0.1 * TIME_SEC)

#define HEARTBEAT_REC (1.0 * TIME_SEC)
#define HEARTBEAT_OFFSET (0.0 * TIME_SEC)


#define SRV_HEARTBEAT_LED_PIN LED_BUILTIN


#endif