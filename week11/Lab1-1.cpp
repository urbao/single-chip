#include "mbed.h"

DigitalOut led[3] = {LED1,LED2,LED3};

int main()
{   
    int counter=0;
    int idx=0;
    printf("LAB 1\r\n"); 
    
    while(1) {
        idx=counter%3;
        led[idx].write(1);
        wait(1);
        led[idx].write(0);
        counter++;
    }
}
