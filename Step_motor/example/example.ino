#include <Step_motor.h>
Step_motor Karuzela1(28,25,26,24,22,11);
Step_motor Karuzela2(38,46,40,42,44,9);
Step_motor Tasmociag(36,29,34,32,30,8);

void setup() {
  Serial.begin(2000000);
  Step_motor::timer4_setup();
  Karuzela1.enable();
  Karuzela1.rotate(6400);
  Karuzela2.enable();
  Karuzela2.rotate(6400);
  Tasmociag.set_res(2);
  Tasmociag.set_freq(125);
  Tasmociag.enable();
  Tasmociag.rotate(-32000);

}

void loop() {
 delay(1);
}
