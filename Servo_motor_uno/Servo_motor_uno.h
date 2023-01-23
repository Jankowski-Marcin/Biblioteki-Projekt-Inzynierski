#ifndef SERVO_MOTOR_UNO_H
#define SERVO_MOTOR_UNO_H
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
    Arduino_pin pin;
    
  public:
    Servo_motor(uint8_t pin_number, uint16_t starting_pos=100);

    void set_position(uint16_t pos);

    void attach_predefined(uint16_t* ptr, uint8_t pos_cnt);

    void set_predefined(uint8_t pos_index);
    
    static void compb_routine(void);
    
    static void compa_routine(void);
    
    static void timer1_setup(void);    
};

#endif
