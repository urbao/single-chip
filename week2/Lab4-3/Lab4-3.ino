#include <Keypad.h> //引用Keypad函式庫
#define KEY_ROWS 3 //按鍵模組的列數
#define KEY_COLS 3 //按鍵模組的行數

const byte colPins[3] = {13, 12, 11};
const byte rowPins[3] = {A0, A1, A2};
const char keymap[KEY_ROWS][KEY_COLS] = {
    {'1','2','3'}, 
    {'4','5','6'}, 
    {'7','8','9'},
};
const int SEG_data[10][8] = {{1, 1, 1, 1, 1, 1, 0, 0},  //"0"  //資料線
                       {0, 1, 1, 0, 0, 0, 0, 0},  //"1"
                       {1, 1, 0, 1, 1, 0, 1, 0},  //"2"
                       {1, 1, 1, 1, 0, 0, 1, 0},  //"3"
                       {0, 1, 1, 0, 0, 1, 1, 0},  //"4"
                       {1, 0, 1, 1, 0, 1, 1, 0},  //"5"
                       {1, 0, 1, 1, 1, 1, 1, 0},  //"6"
                       {1, 1, 1, 0, 0, 0, 0, 0},  //"7"
                       {1, 1, 1, 1, 1, 1, 1, 0},  //"8"
                       {1, 1, 1, 0, 0, 1, 1, 0}};  //"9"
const int SEG_COM = 9;  //控制線

Keypad myKeypad = Keypad(makeKeymap(keymap),rowPins,colPins,KEY_ROWS,KEY_COLS);

void setup(){
  Serial.begin(115200);
  for(int i=2; i<=9; i++){
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);  //共陽極
  }
  for(int i=0; i<3; i++){
    pinMode(rowPins[i], INPUT_PULLUP);
    pinMode(colPins[i], OUTPUT);
    digitalWrite(colPins[i], HIGH);
  }
}

void loop(){
    //透過Keypad函式庫裡的getkey()方法讀取按鍵的字元
    char key = myKeypad.getKey();
    if(key){    //若有按鍵按下則顯示按下的字元
        Serial.println(key);
        int num = key - 48;
        digitalWrite(SEG_COM, LOW);  //觸發第i位數顯示數字
        SEG_Drive(num);  //資料線寫入數值
        delay(5);
    }
    
    
}

void SEG_Drive(int number){  //將字元變數從SEG_data[][]找到相對應的位置，並寫入a~g中
  for(int i = 2; i<9; i++)
  {
    // i: pin腳
    // number: 要顯示的數字
    // pos: 亮的位置
    int pos = i-2;
    digitalWrite(i,SEG_data[number][pos]);
  }
}
