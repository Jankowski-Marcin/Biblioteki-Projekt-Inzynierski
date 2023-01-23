#include "Servo_motor_mega.h"
#include "Arduino_pin.h"
#include <avr/io.h>
#include <avr/interrupt.h> 

Servo_motor::Servo_motor(uint8_t pin_number, uint16_t pos):
  pin(pin_number){
  pin.mode(1,0); 
  instance[cnt]=this;
   ++cnt;
  pozycja=0; 
  if(pos>500){ 
    pos=500;
  }
  pulse_width=pos+100;
}

void Servo_motor::set_position(uint16_t pos){
  if(pos>500){ 
    pos=500;
  }
  pulse_width=100+pos;
}

void Servo_motor::attach_predefined(uint16_t* ptr, uint8_t pos_cnt){
  predefined_pos_cnt=pos_cnt;
  predefined_pos_ptr=ptr;
}  
    
void Servo_motor::set_predefined(uint8_t pos_index){
  if(pos_index>=predefined_pos_cnt)
  return;
  pozycja=pos_index;
  set_position(*(predefined_pos_ptr+pos_index));
}
  
void Servo_motor::compb_routine(void){
  instance[inc]->pin.set(0);
  ++inc;
  if(inc<cnt){//obsługa kolejnego obiektu klasy
    instance[inc]->pin.set(1);
    OCR5B+=instance[inc]->pulse_width;
  }
}
  
void Servo_motor::compa_routine(void){
  inc=0;// zaczynamy obsługę obiektów od nowa
  instance[0]->pin.set(1);
  OCR5B=instance[0]->pulse_width;
}
  
void Servo_motor::timer5_setup(void){
  cli();
  //zerowanie kontronych rejestrów timera 1
  TCCR5A=0;
  TCCR5B=0;
  TCCR5C=0;
  //zerowanie timera
  TCNT5=0;
  // przejśćie do trybu CTC (Clear Timer on Compare match - zerowanie timera po osiągnięciu zadanej wartości) 
  TCCR5B|=(1<<WGM52);
  
  //ustawienie prescalera na 64
  TCCR5B|=(1<<CS20);
  TCCR5B|=(1<<CS21);   
   
  //zadana wartość odliczania w rejestrze komperatora A(16MHz /64) /1kHz -1 = 250 w ten sposób osiągniemy częstotliwość 1kHz
  OCR5A=5000;  
  OCR5B=300; 
    
  // uruchomienie przerwań na komperatorze A  
  TIMSK5|= (1<<OCIE5A); 
  TIMSK5|= (1<<OCIE5B); 
  sei();
}

uint8_t Servo_motor::get_pos(void){
  return pozycja;
}
  
     

//inicjalizacja pól statycznych
uint8_t Servo_motor::cnt=0;
uint8_t Servo_motor::inc=0;
Servo_motor *Servo_motor::instance[7];

//przypisanie rutyn obsługujących przerwania
ISR(TIMER5_COMPA_vect){
  Servo_motor::compa_routine();
}
ISR(TIMER5_COMPB_vect){
  Servo_motor::compb_routine();
}
