#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include "mbed.h"

/** Ultrasonic Class
* This class is intended to be used with a 
* ultrasonic sensor HC-SR04.
* Once initialized the Ultrasonic object just call the read function to 
* get the distance from object.
*/
class Ultrasonic
{
public :
    /** Constructor
    * 
    * @note This is used to initialize the ultrasonic object corresponding to one sensor, 
    * just pass as input the pin where the sensor is connected (they must be digital pins).
    *
    * @param trigger the trigger pin name
    * @param echo the echo pin name
    *
    */
    Ultrasonic(PinName trigger, PinName echo);
    
    /** Function to read the distance in cm
    *
    * @note the distance is read internally every 60 ms so invoke this function
    *       not less than every 60 ms
    * @return
    *       0 if timeout(50ms) elapsed (error or out of range measure), 
    *       1-400 distance from object in cm
    * 
    */
    int read_cm();

private :
    DigitalOut _trigger;
    InterruptIn _echo;
    Timer timer;
    Ticker tick;
    Timeout timeout;
    int DistanceCM;
        
    void start();
    void stop();
    void trig();
    void Ultrasonic_init();
    void timeout_err();
};

#endif
