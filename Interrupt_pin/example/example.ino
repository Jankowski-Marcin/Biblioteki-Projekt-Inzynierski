#include <Interrupt_pin.h>
Interrupt_pin Stykowy1(18);
Interrupt_pin Stykowy2(19);
Interrupt_pin Odbiciowy1(2);
Interrupt_pin Odbiciowy2(3);
void fun1(void){
  Serial.println("stykowy1");
}

void fun2(void){
  Serial.println("stykowy2");
}
void fun3(void){
  Serial.println("odbiciowy1");
}

void fun4(void){
  Serial.println("odbiciowy2");
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(2000000);
  Stykowy1.mode(0,1);
  Stykowy1.attach2intr(&fun1,2);
  Stykowy1.intr_on();
  Stykowy2.mode(0,1);
  Stykowy2.attach2intr(&fun2,2);
  Stykowy2.intr_on();
  Odbiciowy1.mode(0,0);
  Odbiciowy1.attach2intr(&fun3,2);
  Odbiciowy1.intr_on();
  Odbiciowy2.mode(0,0);
  Odbiciowy2.attach2intr(&fun4,2);
  Odbiciowy2.intr_on();
}

void loop() {
  
  /*
  Serial.println("czujniki on");
  delay(5000);
  Stykowy1.intr_on(1);
  Odbiciowy1.intr_on(1);
  Stykowy2.intr_on(1);
  Odbiciowy2.intr_on(1);
  */
}
