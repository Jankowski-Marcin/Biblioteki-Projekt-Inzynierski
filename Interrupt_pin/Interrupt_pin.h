#ifndef INTERRUPT_PIN_H
#define INTERRUPT_PIN_H

#include <avr/io.h>
#include <Arduino_pin.h>

class Interrupt_pin:public Arduino_pin{
  public:

  static Interrupt_pin *arr[6];

  protected:
  void(*user_func)(void);

  uint8_t intr_nbr;

  uint8_t intr_mask;

  uint8_t intr_mode;

  public:

  Interrupt_pin(uint8_t pin_number);

  void attach2intr(void (*input_user_func)(void), uint8_t mode);
      
  void intr_on(uint8_t mode=1);
    
  void intr_off(void);

  void intr_routine(void);

  static int8_t pin2interrupt(uint8_t pin_number);
};






#endif
