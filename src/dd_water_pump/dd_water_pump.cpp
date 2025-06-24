
#include "dd_water_pump.h"
#include "Arduino.h"

int dd_water_pump_state = DD_WATER_PUMP_OFF;
int dd_water_pump_relay = ED_RELAY_ID_6;

int dd_water_pump_op_cnt = 0;

int dd_water_pump_set_state(int state)
{
    if (state == DD_WATER_PUMP_ON)
    {
        dd_water_pump_state = DD_WATER_PUMP_ON;
    }
    else
    {
        dd_water_pump_state = DD_WATER_PUMP_OFF;
    }
    return dd_water_pump_state;
}

int dd_water_pump_get_state()
{
    return dd_water_pump_state;
}

int dd_water_pump_off()
{
    int state = dd_water_pump_set_state(DD_WATER_PUMP_OFF);
    return state;
}

int dd_water_pump_on(int time)
{
    int state = dd_water_pump_set_state(DD_WATER_PUMP_ON);
    dd_water_pump_op_cnt = time;
    return state;
}


void dd_water_pump_setup()
{
    dd_water_pump_off();
}

void dd_water_pump_loop()
{
    if (dd_water_pump_op_cnt > -1) // if not continous
    {
        if (--dd_water_pump_op_cnt <= 0)// decrement
        {
            dd_water_pump_op_cnt = 0;
            dd_water_pump_state = DD_WATER_PUMP_OFF;//change to off
        }
    }

    if (dd_water_pump_state == DD_WATER_PUMP_ON)
    {
        ed_relay_on(dd_water_pump_relay);
    }
    else
    { // stop
        ed_relay_off(dd_water_pump_relay);
        dd_water_pump_op_cnt = 0;
        dd_water_pump_state = DD_WATER_PUMP_OFF;
    }
}
