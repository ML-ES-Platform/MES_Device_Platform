#ifndef ED_ENCODER_H_
#define ED_ENCODER_H_

#ifndef ED_ENCODER_PIN_A
#define ED_ENCODER_PH_A 2
#endif
#ifndef ED_ENCODER_PIN_B
#define ED_ENCODER_PH_B 3
#endif
#include "stdint.h"

void ed_encoder_setup();
void ed_encoder_loop();

int16_t ed_encoder_get_counter(); 
int16_t ed_encoder_set_counter(int16_t cnt);
int16_t ed_encoder_reset_counter();

void ed_encoder_report();

#endif
