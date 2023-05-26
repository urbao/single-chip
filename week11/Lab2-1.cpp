#include "mbed.h"

DigitalIn  button(USER_BUTTON); //the button on your board
DigitalOut led[3] = {LED1,LED2,LED3};

int main()
{   
    int i = 2;
    // 0: reverse direction
    // 1: normal direction
    int state=0;
    bool state_change=false;
    
    button.mode(PullNone);

    while(1) {
        if(button.read()==1){
            led[i].write(1);
            if(state_change==false){
                if(state==0)state=1;
                else state=0;
                state_change=true;
            }
        }
        else if(state==0){
                led[i].write(1);
                wait(1);
                led[i].write(0);
                state_change=false;
                if(i==0)i=2;
                else i--;
            }
            else{
                led[i].write(1);
                wait(1);
                led[i].write(0);
                state_change=false;
                if(i==2)i=0;
                else i++;
            }
    }
}
