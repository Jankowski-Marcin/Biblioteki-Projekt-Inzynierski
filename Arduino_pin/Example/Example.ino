#include <Arduino_pin.h>
Arduino_pin stykowy(18);

void setup() {
  // put your setup code here, to run once:
  stykowy.mode(0,1);
  Serial.begin(2000000);
}

void loop() {
  Serial.println(stykowy.input());
  delay(500);

}
