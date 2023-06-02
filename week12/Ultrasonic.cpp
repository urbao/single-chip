#include "mbed.h"
#include "Ultrasonic.h"


Ultrasonic::Ultrasonic(PinName trigger, PinName echo): _trigger(trigger) , _echo(echo) 
{
    Ultrasonic_init();
}

int Ultrasonic::read_cm()
{
    return DistanceCM;
}

void Ultrasonic::start()
{
    timer.start();
}

void Ultrasonic::stop()
{
    DistanceCM = int(timer.read_us()/58);
    timer.stop();
    timer.reset();
    timeout.detach();
}

void Ultrasonic::timeout_err()
{
    // Timeout elapsed -> there is some problem
    // out the distance to zero to highligth error
    
    DistanceCM = 0;
}

void Ultrasonic::trig()
{
    timeout.attach(this, &Ultrasonic::timeout_err, 0.05);
    _trigger = 1;
    wait_us(500);
    _trigger = 0;
}

void Ultrasonic::Ultrasonic_init()
{
    DistanceCM = 0;
    timer.reset();
    _echo.rise(this,&Ultrasonic::start);
    _echo.fall(this,&Ultrasonic::stop);
    tick.attach(this,&Ultrasonic::trig,0.06);
}
