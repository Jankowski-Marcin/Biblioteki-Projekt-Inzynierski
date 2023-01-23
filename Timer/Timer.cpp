#include "Timer.h"
#include <avr/io.h>
#include "wiring_private.h"

  Timer::Timer(void){
    instance[cnt]=this;
    cnt++;
    tim=0;
  }
  
  void Timer::in(uint8_t input){
    tim=input;
  }

  bool Timer::out(void){
    return !tim;
  }
   
 void Timer::intr_routine(void){
    for(uint8_t i; i<cnt; ++i){
      if(instance[i]->tim)
      --(instance[i]->tim);      
    }
  }

  void Timer::timer3_setup(void){
    TCCR3A=0;
    TCCR3B=0;
    TCNT3=0;

    TCCR3B|=0b00001100;
    OCR3A= 6250;
    TIMSK3|=0b00000010;
  }
  uint8_t Timer::cnt=0;
  Timer *Timer::instance[MAX_TIMER_CNT];

  ISR(TIMER3_COMPA_vect){
    Timer::intr_routine();
  }

  
