
#include "dd_valve.h"
#include "Arduino.h"

int dd_valve_state[DD_VALVE_NR_OF];

int dd_valve_relay[DD_VALVE_NR_OF] = {
    ED_RELAY_HUMIDIFY_ID, // DD_VALVE_ID_4
    ED_RELAY_MOIST_ID, // DD_VALVE_ID_5
};

int dd_valve_op_cnt[DD_VALVE_NR_OF] ;

int dd_valve_set_state(size_t valve_it, int state)
{
    if (state == DD_VALVE_OPEN)
    {
        dd_valve_state[valve_it] = DD_VALVE_OPEN;
    }
    else
    {
        dd_valve_state[valve_it] = DD_VALVE_CLOSE;
    }
    return dd_valve_state[valve_it];
}

int dd_valve_get_state(size_t valve_it)
{
    return dd_valve_state[valve_it];
}

int dd_valve_off(size_t valve_it)
{
    int state = dd_valve_set_state(valve_it, DD_VALVE_CLOSE);
    return state;
}

int dd_valve_on(size_t valve_it, int time)
{
    int state = dd_valve_set_state(valve_it, DD_VALVE_OPEN);
    dd_valve_op_cnt[valve_it] = time/DD_VALVE_REC; // set operation count
    return state;
}

void dd_valve_setup()
{
    for (size_t valve_it = 0; valve_it < DD_VALVE_NR_OF; valve_it++)
    {
        dd_valve_off(valve_it);
        dd_valve_op_cnt[valve_it] = 0; // set to off
        dd_valve_state[valve_it] = DD_VALVE_CLOSE; // set to off
    }
}

void dd_valve_loop()
{
    for (size_t valve_it = 0; valve_it < DD_VALVE_NR_OF; valve_it++)
    {
        if (dd_valve_op_cnt[valve_it] > -1) // if not continous
        {
            if (--dd_valve_op_cnt[valve_it] <= 0) // decrement
            {
                dd_valve_op_cnt[valve_it] = 0;
                dd_valve_state[valve_it] = DD_VALVE_CLOSE; // change to off
            }
        }

        int relay_it = dd_valve_relay[valve_it];
        if (dd_valve_state[valve_it] == DD_VALVE_OPEN)
        {
            ed_relay_on(relay_it);
        }
        else
        { // stop
            ed_relay_off(relay_it);
            dd_valve_op_cnt[valve_it] = 0;
            dd_valve_state[valve_it] = DD_VALVE_CLOSE;
        }
    }
}
