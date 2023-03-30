#include <BluetoothSerial.h>

BluetoothSerial BT; // Our Android Phone

const int SEG_COM[4]={12, 18, 5, 4}; // control signal line
const int SEG[8]={16, 19, 27, 25, 33, 17, 14, 26}; // data signal line
const int SEG_data[10][8]={{1, 1, 1, 1, 1, 1, 0, 0},  //"0"
                     {0, 1, 1, 0, 0, 0, 0, 0},  //"1"
                     {1, 1, 0, 1, 1, 0, 1, 0},  //"2"
                     {1, 1, 1, 1, 0, 0, 1, 0},  //"3"
                     {0, 1, 1, 0, 0, 1, 1, 0},  //"4"
                     {1, 0, 1, 1, 0, 1, 1, 0},  //"5"
                     {1, 0, 1, 1, 1, 1, 1, 0},  //"6"
                     {1, 1, 1, 0, 0, 0, 0, 0},  //"7"
                     {1, 1, 1, 1, 1, 1, 1, 0},  //"8"
                     {1, 1, 1, 0, 0, 1, 1, 0}};  //"9"

bool start=false; // define current states(counting or stop)
int number=0; // the counter number(add 1 every 0.1 sec)
int disp[4]={0};
unsigned long preTime=0; // used to record the time when pause
unsigned long currTime=0; // used to record current time

void setup(){
    Serial.begin(9600);
    BT.begin("ESP32_2");
    // initialize pin mode
    // SEG_COM
    for(int i=0;i<4;i++){
        pinMode(SEG_COM[i], OUTPUT);
        digitalWrite(SEG_COM[i], HIGH);
    }
    // SEG
    for(int i=0;i<8;i++){
        pinMode(SEG[i], OUTPUT);
        digitalWrite(SEG[i], HIGH); // Common Anode
    }
}

void loop(){
    if(BT.available()){
        if(BT.read()=='1')start_or_pause(start);
        else if(BT.read()=='0')reset_counter();
        else Serial.println("Something wrong: BT input is not allowed");
    }
}

// Start counting or Stop counting
// parameter start: current is counting or not
void start_or_pause(bool start){
    // already counting, so pause it
    if(start==true){
        currTime=0;
        preTime=0;
        start=false;
    }
    // already pause, start counting
    else{
        while(true){
            currTime=millis();
            if(currTime-preTime>=100){
                preTime=currTime;
                number++;
                disp_num(number);
            }
        }
        start=true;
    }
}

// used to display number
void disp_num(int number){
    int thousand=number/1000;
    int hundred=number%1000/100;
    int tenth=number%100/10;
    int digit=number%10;
    disp[0]=thousand;
    disp[1]=hundred;
    disp[2]=tenth;
    disp[3]=digit;
    for(int i=0;i<4;i++){
        digitalWrite(SEG_COM[i], LOW);
        SEG_Drive(disp[i]);
        delay(5);
        digitalWrite(SEG_COM[i], HIGH);
    }
}

void SEG_Drive(int number){  //將字元變數從SEG_data[][]找到相對應的位置，並寫入a~g中
    for(int i = 0; i<8; i++){
        digitalWrite(SEG[i], SEG_data[number][i]);
    }
    return;
}

// when pressing 0, reset the counter
void reset_counter(){
    start=false;
    number=0;
    preTime=0;
    currTime=0;
    return;
}