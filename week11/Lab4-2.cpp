#include "mbed.h"
 
Ticker tick[2];
DigitalOut blinkled[2] = {LED1, LED3};

void change0() {
    blinkled[0]=!blinkled[0];
}

void change1() {
    blinkled[1]=!blinkled[1];
}
 
int main() {
    tick[0].attach(&change0, 0.5);
    tick[1].attach(&change1, 2);
}
