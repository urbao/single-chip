#include <Keypad.h> //引用Keypad函式庫
#define KEY_ROWS 4 //按鍵模組的列數
#define KEY_COLS 4 //按鍵模組的行數

const byte colPins[4] = {2, 3, 4, 5};
const byte rowPins[4] = {A0, A1, A2, A3};
const char keymap[KEY_ROWS][KEY_COLS] = {
    {'1','2','3','A'}, 
    {'4','5','6','B'}, 
    {'7','8','9','C'},
    {'*','0','#','D'}
};
char buf[100];
int idx = 0;
Keypad myKeypad = Keypad(makeKeymap(keymap),rowPins,colPins,KEY_ROWS,KEY_COLS);
void setup(){
    Serial.begin(115200);
}

void loop(){
    //透過Keypad函式庫裡的getkey()方法讀取按鍵的字元
    char key = myKeypad.getKey();
    if(key == '*'){    //若有按鍵按下則顯示按下的字元
      for(int i = 0; i <= idx; i++)
      {
        Serial.print(buf[i]);
      }
      Serial.println("");
      idx=0;
    }
    if(key && key != '*')
    {
      buf[idx] = key;
      idx++;
    }
    
}
