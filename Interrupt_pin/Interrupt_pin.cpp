#include "Interrupt_pin.h"
#include "wiring_private.h"
#include <avr/io.h>

#define ONCE 1
#define NODEBOUNCER 0
#define WITHDEBOUNER 2


void do_nothing(void){
  
}

int8_t Interrupt_pin::pin2interrupt(uint8_t pin_number){
  switch(pin_number){
    case 2: return 4;
    case 3: return 5;
    case 18: return 3;
    case 19: return 2;
    case 20: return 1;
    case 21: return 0;
    default: return -1;
  }
}
Interrupt_pin::Interrupt_pin(uint8_t pin_number)
:Arduino_pin(pin_number){
  
  intr_nbr=pin2interrupt(pin_number);
  
  if(intr_nbr<0)
  return;

  arr[intr_nbr]=this;

  intr_mask=(1<<intr_nbr);

} 
void Interrupt_pin::attach2intr(void (*input_user_func)(void), uint8_t mode){
  if(intr_nbr<0)
    return;
    
  user_func=input_user_func;
  if(intr_nbr<4){
    EICRA&=(~(3<<(intr_nbr*2)));
    EICRA|=(mode<<(intr_nbr*2));
  }
  if(intr_nbr>3){
    EICRB&=(~(3<<((intr_nbr-4)*2)));
    EICRB|=(mode<<((intr_nbr-4)*2));
  }
  
}

void Interrupt_pin::intr_on(uint8_t mode=1){
    
  intr_mode=mode;

  EIFR|=(intr_mask);

  EIMSK|=(intr_mask);

}

void Interrupt_pin::intr_off(){
  intr_mode=1;
  EIMSK&=(~(intr_mask));
  
}

void Interrupt_pin::intr_routine(void){
  if(intr_mode){
    EIMSK&=(~intr_mask);
  }
  user_func(); 
}  
  
Interrupt_pin *Interrupt_pin::arr[6];

ISR(INT0_vect){
   Interrupt_pin::arr[0]->intr_routine();
}

ISR(INT1_vect){
   Interrupt_pin::arr[1]->intr_routine();
}

ISR(INT2_vect){
   Interrupt_pin::arr[2]->intr_routine();
}

ISR(INT3_vect){
   Interrupt_pin::arr[3]->intr_routine();
}

ISR(INT4_vect){
   Interrupt_pin::arr[4]->intr_routine();
}

ISR(INT5_vect){
   Interrupt_pin::arr[5]->intr_routine();
}


    

 

  
  

  

  

  

  
