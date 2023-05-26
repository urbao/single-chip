#include "mbed.h"

Timer timer;
DigitalIn button(USER_BUTTON,PullDown);
int s0,t0=0,t1=0;

int button_debounce_read(){
    // read initial state of button
    s0=button;
    t0=timer.read_ms();
    // use timer to wait for 50ms
    while((t1-t0)<50){
        t1=timer.read_ms();
    }
    // still same state, meaning the button is pressed
    timer.reset();
    if(button==s0){
        while(button==s0){
        }
        return 1;
    }
    else return 0;
}

int main()
{
    timer.start();
    s0 = button.read();
    int cnt = 0;
    while(1)
    {
        if(button.read()==1){
            cnt+=button_debounce_read();
            printf("Count: %d\r\n", cnt);
        }
    }
}
