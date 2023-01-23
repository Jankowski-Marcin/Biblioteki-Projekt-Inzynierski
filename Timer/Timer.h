#ifndef TIMER_H
#define TIMER_H

#include <avr/io.h>
#define MAX_TIMER_CNT 17

class Timer{
  private:
  
  static Timer *instance[MAX_TIMER_CNT];
  static uint8_t cnt;

  uint8_t tim;
  
  public:
  Timer(void);
  
  void in(uint8_t input);
  
  bool out(void);
  
  static void intr_routine(void);
  
  static void timer3_setup(void);
};

#endif
