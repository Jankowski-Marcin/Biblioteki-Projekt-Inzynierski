#include "Arduino_pin.h"
#include "wiring_private.h"
#include <avr/io.h>

Arduino_pin::Arduino_pin(uint8_t pin_number){
  uint8_t port; 
  mask    = digitalPinToBitMask( pin_number );
  port    = digitalPinToPort( pin_number );
  reg = portOutputRegister( port );                        
}

void Arduino_pin:: mode(bool IO, bool Pullup){
  if(IO){
    *(reg-1)|=mask;
  }
  else{
    *(reg-1)&=~mask; 
    set(Pullup);
  }
}

void Arduino_pin::set(bool state){
  if(state){
    *reg|=mask; 
  }else{
    *reg&=~mask; 
  }
}
   
void Arduino_pin::toggle(void){
  *reg^=mask;
}

bool Arduino_pin::input(void){
  return *(reg-2)&=mask;
}
