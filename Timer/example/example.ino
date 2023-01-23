#include <Timer.h>
Timer Tim1;
Timer Tim2;

void setup() {
  Serial.begin(2000000);
  Timer::timer3_setup();
  Tim1.in(10);
  Tim2.in(15);
  
}

void loop() {
  Serial.print(Tim1.out());
  Serial.print(" ");
  Serial.println(Tim2.out());
  delay(100);
}
