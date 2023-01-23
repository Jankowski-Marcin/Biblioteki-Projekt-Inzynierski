#ifndef SERVO_MOTOR_MEGA_H
#define SERVO_MOTOR_MEGA_H
#include <avr/io.h>
#include "Arduino_pin.h"

class Servo_motor{
  private:
    static uint8_t cnt;
    static uint8_t inc;
    static Servo_motor *instance[7];
    uint16_t pulse_width;
    uint16_t *predefined_pos_ptr;
    uint8_t predefined_pos_cnt;
    uint8_t pozycja;
    Arduino_pin pin;
    
  public:
    //konstruktor
    Servo_motor(uint8_t pin_number, uint16_t starting_pos=100);

    //metoda zadająca pozycję
    void set_position(uint16_t pos);

    //metoda wczytująca wskaźnik na tablicę pozycji predefiniowanych
    void attach_predefined(uint16_t* ptr, uint8_t pos_cnt);

    //metoda ustawiająca jedną z pozycji predefiniowanych
    void set_predefined(uint8_t pos_index);

    //statyczna rutyna na przerwaniu komperatora B
    static void compb_routine(void);

    //statyczna rutyna na przerwaniu komperatora A
    static void compa_routine(void);

    //statyczna funkcja przygotowująca timer5 do współpracy z serwami
    static void timer5_setup(void);  

    //metoda zwracająca pozycję serva
    uint8_t get_pos(void);
};

#endif
