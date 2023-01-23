#ifndef STEP_MOTOR_H
#define STEP_MOTOR_H
#include <Arduino_pin.h>
#include <inttypes.h>

class Step_motor{
  private:
    //numery pinów sterownika:
    Arduino_pin pin_en;
    Arduino_pin pin_dir;
    Arduino_pin pin_m1;
    Arduino_pin pin_m2;
    Arduino_pin pin_m3;
    Arduino_pin pin_st;
    
    static uint8_t cnt;
    
    
    //zmienne pomocnicze:
    uint8_t res;    //aktualnie ustawiona rozdzielczość
    bool en;        //aktualny stan na wyjściu enable
    bool dir;       //aktualnie ustawiony kierunek obrotu
    bool st;        //aktualny stan na wyjściu step
    int steps; //liczba zadanych kroków
    uint8_t intr_mask;
    uint8_t pulse_width;
    volatile uint16_t *comp_reg;

    public:
    static Step_motor *instance[3];

  public:
    //Konstruktor
    Step_motor(uint8_t pin_enable, uint8_t pin_direction, uint8_t pin_ms1, uint8_t pin_ms2, uint8_t pin_ms3, uint8_t pin_step);
    
    //Metoda ustawiająca rozdzielczość na sterowniku  
    void set_res(uint8_t resolution);

    //Metoda_ustawiająca czestotliwość stepa
    void set_freq(uint8_t period);
    
    //metoda aktywująca sterownik
    void enable(void);
    
    //metoda dezaktywująca sterownik
    void disable(void);
    
    //metoda zadająca liczbę kroków
    void rotate(int steps_to_rotate);
    
    //rutyna wykonywana przez przerwanie zegarowe
    void isr_routine(void);
    
    //metoda zwracająca stan silnika (1-pracuje, 0-stoi);
    bool state(void);	
	    
    //setup timera pod pracę z silnikami krokowymi
    static void timer4_setup(void);

};
#endif
