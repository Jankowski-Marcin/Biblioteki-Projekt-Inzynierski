#include <Servo_motor_uno.h>

Servo_motor Obrotnica(12,250);
uint16_t pozycje[3]={200,250,300};
void setup() {
  Servo_motor::timer1_setup();
  Obrotnica.attach_predefined(&pozycje[0],3);

}

void loop() {
  Obrotnica.set_predefined(0);
  delay(2000);
  Obrotnica.set_predefined(1);
  delay(2000);
  Obrotnica.set_predefined(2);
  delay(2000);


}
