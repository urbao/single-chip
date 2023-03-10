#include <Keypad.h>

#define ROWS 4 
#define COLS 4
const byte colPins[4] = {7, 8, 9, 10};
const byte rowPins[4] = {3, 4, 5, 6};
// define keymap of Keypad
const char keymap[ROWS][COLS] = {
    {'1','2','3','+'}, 
    {'4','5','6','-'}, 
    {'7','8','9','*'},
    {'$','0','=','/'}
};

// create instance of Keypad
Keypad myKeypad=Keypad(makeKeymap(keymap), rowPins, colPins, ROWS, COLS);

void setup(){
    Serial.begin(9600);
}

// initailize global variables
String input_num[2]={""}; // used to store user input number
char operand='#'; // store the arithmetic operand symbol
int idx=0; // idx used to decide which input_num[idx] store newKey

void loop(){
    char newKey=myKeypad.getKey();
    // when input char is some digit number
    if(newKey!=NO_KEY && isDigit(newKey)){
       input_num[idx]+=newKey; // append the number to input_num[idx] 
        Serial.print(newKey);
    }
    // when input char is operators
    if(newKey!=NO_KEY && (newKey=='+'||newKey=='-'||newKey=='*'||newKey=='/')){
        idx=1; // change stored input number index to second
        operand=newKey; // store operand with input newKey
        Serial.print(newKey);
    }
    // when input char is RESET
    if(newKey=='$'){
        input_num[0]="";
        input_num[1]="";
        operand='#';
        idx=0;
        Serial.println("");
        Serial.println("RESET");
    }
    if(newKey=='='){
       Serial.print(newKey);
        if(operand=='+')Serial.println(String(input_num[0].toInt()+input_num[1].toInt()));
        if(operand=='-')Serial.println(String(input_num[0].toInt()-input_num[1].toInt()));
        if(operand=='*')Serial.println(String(input_num[0].toInt()*input_num[1].toInt()));
        if(operand=='/')Serial.println(String(input_num[0].toInt()/input_num[1].toInt()));
        // reset all variables to original stats
        input_num[0]="";
        input_num[1]="";
        operand='#';
        idx=0;
    }
}
