#include "mbed.h"
 
InterruptIn button(USER_BUTTON);
DigitalOut led(LED1);
DigitalOut blinkled(LED3);
Timer timer;
 
void change() {
    timer.reset();
    while(timer.read_ms()<100);
    if(button.read()==1){
        led=!led;
    }
    return;
}
 
int main() {
    timer.start();
    button.rise(&change);  // pos-edge execute flip()
    // LED3 blinks for a second
    while(1){
        blinkled = !blinkled;
        wait(2);
    } 
}
