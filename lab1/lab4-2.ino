#include <Keypad.h> 
#define KEY_ROWS 4 
#define KEY_COLS 4

const byte colPins[4] = {2, 3, 4, 5};
const byte rowPins[4] = {A0, A1, A2, A3};
const char keymap[KEY_ROWS][KEY_COLS] = {
    {'1','2','3','A'}, 
    {'4','5','6','B'}, 
    {'7','8','9','C'},
    {'*','0','#','D'}
};
Keypad myKeypad = Keypad(makeKeymap(keymap),rowPins,colPins,KEY_ROWS,KEY_COLS);

void setup(){
    Serial.begin(115200);
}

void loop(){
   // Use the method of Keypad library 
    char key = myKeypad.getKey();
    if(key){    // output key iff there's key pressed
        Serial.println(key);
    }
}
