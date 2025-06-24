#include "ed_encoder.h"
#include "Arduino.h"


/*     Arduino Rotary Encoder Tutorial
 *      
 *  by Dejan Nedelkovski, www.HowToMechatronics.com
 *  
 */
 


 int16_t counter = 0; 
 int aState;
 int aLastState;  

 int16_t  ed_encoder_get_counter(){
    return counter;
 }

int16_t  ed_encoder_set_counter(int16_t cnt){
    counter = cnt;
    return counter;
}
int16_t  ed_encoder_reset_counter(){
    counter = ed_encoder_set_counter(0);
    return counter;
}

 void ed_encoder_setup() { 
   pinMode (ED_ENCODER_PH_A,INPUT);
   pinMode (ED_ENCODER_PH_B,INPUT);
   
   // Reads the initial state of the outputA
   aLastState = digitalRead(ED_ENCODER_PH_A);   
 } 

 void ed_encoder_loop() { 
   aState = digitalRead(ED_ENCODER_PH_A); // Reads the "current" state of the outputA
   // If the previous and the current state of the outputA are different, that means a Pulse has occured
   if (aState != aLastState){     
     // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
     if (digitalRead(ED_ENCODER_PH_B) != aState) { 
       counter ++;
     } else {
       counter --;
     }
    //  Serial.print(F("Position: "));
    //  Serial.println(counter);
   } 
   aLastState = aState; // Updates the previous state of the outputA with the current state
 }

 void ed_encoder_report(){
    int16_t cnt = ed_encoder_get_counter();
    Serial.print(F("ED_ENCD: Counter = "));
    Serial.println(cnt);
 }