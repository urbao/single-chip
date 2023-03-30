#include <BluetoothSerial.h>

BluetoothSerial BT; // BT: Android Phone, send one char at a time
const int LED[5]={19, 18, 5, 17, 16}; // five LEDs pin number

void setup(){
    Serial.begin(9600);
    BT.begin("ESP32_2"); // setup BT and its name
    // initialize all pins
    for(int i=0;i<5;i++){
        pinMode(LED[i], OUTPUT);
        digitalWrite(LED[i], LOW);
    }
}

void loop(){
    if(BT.available()){
        if(BT.read()=='0')setAll_LED(0);
        else if(BT.read()=='1')setMarquee_LED(1);
        else if(BT.read()=='2')setMarquee_LED(-1);
        else if(BT.read()=='3')setAll_LED(1);
        else blink_twice();
    }
}

// setup ALL LEDs to same mode
// mode: 0 --> LOW; 1 --> HIGH
void setAll_LED(int mode){
    if(mode==0){
        for(int i=0;i<5;i++){
            digitalWrite(LED[i], LOW);
        }
    }
    else if(mode==1){
        for(int i=0;i<5;i++){
            digitalWrite(LED[i], HIGH);
        }
    }
    else{
        Serial.println("Something wrong: `mode` not allowed in setAll_LED");
    }
}

// use the Marquee to run all LEDs once
// mode: 1: Left->Right; -1: Right->Left
void setMarquee_LED(int mode){
    if(mode==1){
        for(int i=0;i<5;i++){
            digitalWrite(LED[i], HIGH);
            delay(1000);
            digitalWrite(LED[i], LOW);
        }
    }
    else if(mode==-1){
        for(int i=4;i<0;i--){
            digitalWrite(LED[i], HIGH);
            delay(1000);
            digitalWrite(LED[i], LOW);
        }
    }
    else{
        Serial.println("Something wrong: `mode` not allowed in setMarquee_LED");
    }
}

// all LEDs blink twice
void blink_twice(){
    for(int i=0;i<2;i++){
        // first set all LEDs to HIGH
        for(int i=0;i<5;i++){
            digitalWrite(LED[i], HIGH);
        }
        delay(1000);
        // then set all LEDs to LOW
        for(int i=0;i<5;i++){
            digitalWrite(LED[i], LOW);
        }
    }
}