#include "mbed.h"

class LEDcontrol {
public:
    LEDcontrol(PinName pin, PinName pin1){
        _pin = new DigitalOut(LED1);
        _pin1 = new DigitalOut(LED2);
        *_pin = 0;
        *_pin1 = 0;
        state = 0;
    }
    void change() {
     state = 1;
    }
    void flip(){
      if(!state)
      *_pin = !*_pin;
      if(state)
      *_pin1 = !*_pin1;
    }
private:
    DigitalOut *_pin,*_pin1;
    bool state;
};

LEDcontrol led(LED1,LED2);
Timeout t;

int main() {

    t.attach(callback(&led, &LEDcontrol::change), 5.0);
    while(1)
    {
        led.flip();
        wait(0.2);
    } 
}