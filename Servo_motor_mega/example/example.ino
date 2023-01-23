#include <Servo_motor_mega.h>

Servo_motor Podajnik(13);
uint16_t pozycje[3]={50,150,253};

void setup() {
  Servo_motor::timer5_setup();
  Podajnik.attach_predefined(&pozycje[0],3);
}

void loop() {
  Podajnik.set_predefined(0);
  delay(1000);
  Podajnik.set_predefined(1);
  delay(1000);
  Podajnik.set_predefined(2);
  delay(1000);
  

}
