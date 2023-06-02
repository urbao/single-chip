#include "mbed.h"
#include "Ultrasonic.h"
#include "rtos.h"
#include <ctime>
DigitalOut com[2] = {D0,D1};    
DigitalOut seg[8] = {D4,D5,D6,D7,D8,D9,D10,D11};
DigitalOut led[3]={LED1,LED2,LED3};
int disp[2] = {0,0};
int d;
int i = 0;
int table[11][8]=
{
    {1,1,1,1,1,1,0,0}, // 0
    {0,1,1,0,0,0,0,0}, // 1
    {1,1,0,1,1,0,1,0}, // 2
    {1,1,1,1,0,0,1,0}, // 3
    {0,1,1,0,0,1,1,0}, // 4
/*  {a,b,c,d,e,f,g,p}  */  
    {1,0,1,1,0,1,1,0}, // 5
    {1,0,1,1,1,1,1,0}, // 6
    {1,1,1,0,0,0,0,0}, // 7
    {1,1,1,1,1,1,1,0}, // 8
    {1,1,1,0,0,1,1,0}, // 9
    /* external */
    {0,0,0,0,0,0,0,0}  // void
};  
Thread a;
Thread b;
Thread c;
Thread dd;
Timer tt;
int t;

void packing(int num) // 1234 -> [1][2][3][4]
{   
    int tenth=(num/10)%10;
    int digit=(num%10);
    disp[0]=tenth;
    disp[1]=digit;
}

/*void dist(int distance)
{
    d=distance/10;
    packing(d);
}*/


void mapping(int disp)
{
    for(int i =0; i<8;i++)
    {
        seg[i]=table[disp][i];
    }
}

Ultrasonic mu(D2, D3);    //Set the trigger pin to D8 and the echo pin to D9
                                        //have updates every .1 seconds and a timeout after 1
                                        //second, and call dist when the distance changes
// distance < 10cm, red led lighten
void mode1()
{
    while(1)
    {
        a.signal_wait(0x1);
        led[0]=0;
        led[1]=0;
        led[2]=1;
    }
}
// distance = 10~15cm, blue led lighten
void mode2()
{  
    while(1)
    {
        b.signal_wait(0x1);
        led[0]=0;
        led[1]=1;
        led[2]=0;
    }
}
// distance = 15~20cm, green led lighten
void mode3()
{
    while(1)
    {
        c.signal_wait(0x1);
        led[0]=1;
        led[1]=0;
        led[2]=0;
    }
}
// distance > 20cm, all led lighten
void mode4()
{
    while(1)
    {
        dd.signal_wait(0x1);
        led[0]=1;
        led[1]=1;
        led[2]=1;
    }
}

int main()
{   
    tt.reset();
    tt.start();
    while(1)
    {
        //Do something else here
        d = mu.read_cm();     //call checkDistance() as much as possible, as this is where
                                //the class checks if dist needs to be called.
        packing(d);
        a.start(mode1);
        b.start(mode2);
        c.start(mode3);
        dd.start(mode4);
        if(d<10)
        {
            a.signal_set(0x1);
        }
        else if(d>=10 && d<15)
        {
            b.signal_set(0x1);
        }
        else if(d>=15 && d<20)
        {
            c.signal_set(0x1);
        }
        else if(d>=20)
        {
            dd.signal_set(0x1);
        }

        // 七段顯示器
        t = tt.read_ms();
        com[i]=0;  //觸發第i位數顯示數字
        mapping(disp[i]);  //資料線寫入數值
        while(tt.read_ms() <= t+5){}
        com[i]=1;   //結束觸發第i位數
        i = (i+1)%2;

    }
}
