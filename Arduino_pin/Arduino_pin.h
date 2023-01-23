#ifndef ARDUINO_PIN_H
#define ARDUINO_PIN_H

#include <avr/io.h>
class Arduino_pin{
  private:
    //maska bitowa 
    uint8_t mask;
    //adres rejestru
    volatile uint8_t *reg;
    
  public:
    //konstruktor
    Arduino_pin(uint8_t pin_number);
    
    //metoda ustawiająca tryb pracy
    void mode(bool IO, bool Pullup);
    
    //metoda ustawiająca stan wyjścia
    void set(bool state);

    //metoda przełączająca stan wyjścia na przeciwny
    void toggle(void);

    bool input(void);

};
#endif
