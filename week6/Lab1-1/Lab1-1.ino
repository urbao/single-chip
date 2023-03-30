#include <BluetoothSerial.h> // include Bluetooth Library

BluetoothSerial BT; // define BT as a Bluetooth Object(Our Android Phone)
const int LED=19; // define LED pin number

void setup(){
    Serial.begin(9600);
    BT.begin("ESP32_2"); // start BT, and set its name
    // initialize pin number and state(LED default: LOW)
    pinMode(LED, OUTPUT);
    digitalWrite(LED, LOW);
}

void loop(){
    // receive data from phone
    if(BT.available()){
        if(BT.read()=='0')digitalWrite(LED, LOW);
        else if(BT.read()=='1')digitalWrite(LED, HIGH);
        else{
            // other inputs, so blink the LED twice
            for(int i=0;i<2;i++){
                digitalWrite(LED, HIGH);
                delay(1000);
                digitalWrite(LED, LOW);
                delay(1000);
            }
        }
    }
}