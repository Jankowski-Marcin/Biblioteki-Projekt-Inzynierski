#include "Step_motor.h"
#include <Arduino_pin.h>
#include <inttypes.h>  
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>     
#include <Arduino.h>
    
    
  Step_motor::Step_motor(uint8_t pin_enable, uint8_t pin_direction, uint8_t pin_ms1, uint8_t pin_ms2, uint8_t pin_ms3, uint8_t pin_step):
    pin_en(pin_enable),
    pin_dir(pin_direction),
    pin_m1(pin_ms1),
    pin_m2(pin_ms2),
    pin_m3(pin_ms3),
    pin_st(pin_step)
    {
      //tworzenie wskaźnika na instancję klasy
      instance[cnt]=this;
      ++cnt;
      intr_mask=(1<<cnt);
      pulse_width=250;
      if(cnt==1) comp_reg=&OCR4A;
      if(cnt==2) comp_reg=&OCR4B;
      if(cnt==3) comp_reg=&OCR4C;
      
      //ustawienie pinów jako wyjścia
      pin_en.mode(1,0);
      pin_dir.mode(1,0);
      pin_m1.mode(1,0);
      pin_m2.mode(1,0);
      pin_m3.mode(1,0);
      pin_st.mode(1,0);
  
      //ustawienie początkowych stanów pinów
      pin_en.set(1);
      pin_dir.set(1);                     
      pin_m1.set(1);             
      pin_m2.set(1);             
      pin_m3.set(1);             
      pin_st.set(1);             
        
      //przypisanie wartości początkowych zmiennym pomocniczym
      en=1;
      st=1;
      dir=1;
      res=16;    
     
    }
  
  void Step_motor::set_res(uint8_t resolution){ 
    switch(resolution){
      case 1:
        pin_m1.set(0);
        pin_m2.set(0);
        pin_m3.set(0);
        res=resolution;
      break;
            
      case 2:
        pin_m1.set(1);
        pin_m2.set(0);
        pin_m3.set(0);
        res=resolution;
      break;
            
      case 4:
        pin_m1.set(0);
        pin_m2.set(1);
        pin_m3.set(0);
        res=resolution;
      break;
            
      case 8:
        pin_m1.set(1);
        pin_m2.set(1);
        pin_m3.set(0);
        res=resolution;
      break;
             
      case 16:
        pin_m1.set(1);
        pin_m2.set(1);
        pin_m3.set(1);
        res=resolution;
      break;            
      }
    }
  void Step_motor::set_freq(uint8_t period){
    if(period<64) period=65;
    pulse_width=period;
  }
    
  
  void Step_motor::enable(void){
    pin_en.set(0);
    en=0;
    }
      
  void Step_motor::disable(void){
    pin_en.set(1);
    en=1;
    }
  
  void Step_motor::rotate(int steps_to_rotate){
    dir=(steps_to_rotate<0);
    pin_dir.set(dir);
    steps=abs(steps_to_rotate); 
    if(steps) TIMSK4|=intr_mask;
    
  }
      
  void Step_motor::isr_routine(void){
    if(steps>0){
      *comp_reg+=pulse_width;
      pin_st.toggle();
      steps--;
    }
    else{
      TIMSK4&=(~intr_mask); 
    }
  }

  bool Step_motor::state(){
    if(steps>0) return 1;
    return 0;
  }	

  
  void Step_motor::timer4_setup(void){
  cli();
  //zerowanie kontronych rejestrów timera 1
  TCCR4A=0;
  TCCR4B=0;
  TCCR4C=0;
  //zerowanie timera
  TCNT4=0;
  
  //ustawienie prescalera na 64
  TCCR4B|=(1<<CS40);
  TCCR4B|=(1<<CS41);   
   
  //zadana wartość odliczania w rejestrze komperatora A(16MHz /64) /1kHz -1 = 250 w ten sposób osiągniemy częstotliwość 1kHz
  OCR4A=300;  
  OCR4B=300; 
  OCR4C=300; 
    
  sei();
}

  // inicjalizacja pól statycznych
  Step_motor *Step_motor::instance[3];
  uint8_t Step_motor::cnt=0;

  //przypisanie przerwań
    ISR(TIMER4_COMPA_vect){
    Step_motor::instance[0]->isr_routine();
  }

      ISR(TIMER4_COMPB_vect){
    Step_motor::instance[1]->isr_routine();
  }

      ISR(TIMER4_COMPC_vect){
    Step_motor::instance[2]->isr_routine();
  }
