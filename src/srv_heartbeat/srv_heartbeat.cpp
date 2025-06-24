#include "srv_heartbeat.h"
#include "ecu_config.h"
#include "Arduino.h"

static int srv_hearbeat_state = 0;

void srv_heartbeat_setup()
{
    pinMode(SRV_HEARTBEAT_LED_PIN, OUTPUT);
}

void srv_heartbeat_loop()
{
    if (srv_hearbeat_state)
    {
        srv_hearbeat_state = 0;
        digitalWrite(SRV_HEARTBEAT_LED_PIN, LOW);
        Serial.print(F("Heartbeat !!"));
    }
    else
    {
        srv_hearbeat_state = 1;
        digitalWrite(SRV_HEARTBEAT_LED_PIN, HIGH);
    }
}