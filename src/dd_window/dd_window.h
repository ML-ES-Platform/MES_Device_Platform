#ifndef DD_WINDOW_H_
#define DD_WINDOW_H_

#include "ecu_config.h"


#include "stdint.h"

enum dd_windoe_state_t{
    DD_WINDOW_STOP,
    DD_WINDOW_CLOSE,
    DD_WINDOW_OPEN,
    DD_WINDOW_UNKNOWN = -1
};

#ifndef DD_WINDOW_REC
#define DD_WINDOW_REC (100 ) 
#endif

#ifndef DD_WINDOW_OP_D_TIME
#define DD_WINDOW_OP_D_TIME (1.0 * TIME_SEC)
#endif

void dd_window_setup();
void dd_window_loop();

int8_t dd_window_stop();
int8_t dd_window_open(int time);
int8_t dd_window_close(int time);
int8_t dd_window_set_state(uint8_t state);
int8_t dd_window_get_state();

#endif