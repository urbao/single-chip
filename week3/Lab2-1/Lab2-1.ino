#include <Keypad.h>   //引用Keypad函式庫
#include <Password.h> //引用Password函式庫
#define KEY_ROWS 4    //按鍵模組的列數
#define KEY_COLS 4    //按鍵模組的行數

//Keypad設定
const byte colPins[4] = {7, 8, 9, 10};
const byte rowPins[4] = {3, 4, 5, 6};
const char keymap[KEY_ROWS][KEY_COLS] = { {'1','2','3','A'}, 
                                          {'4','5','6','B'}, 
                                          {'7','8','9','C'},
                                          {'*','0','#','D'} };
Keypad myKeypad = Keypad(makeKeymap(keymap),rowPins,colPins,KEY_ROWS,KEY_COLS);

//全域變數設定
Password password = Password("1998111819981118");
String buffer = "";

void setup()
{  
  Serial.begin(9600);
  for( int i=0; i<4; i++)
  {
    pinMode(colPins[i], INPUT);
    pinMode(rowPins[i], INPUT);
  }
}

void loop()
{
//輸入答案
  char key = myKeypad.getKey();
  if(key)//若有按鍵按下則顯示按下的字元
  {    
    if(key >= 48 && key <= 57)
    {
      buffer = buffer + key;
      Serial.println(buffer);
    }
    else if(key != 'A')
    {
      Serial.println("Illegal input!! Please input again.");
      Serial.println("");
      buffer = ""; 
    }
    //判斷答案正確性
    if(key == 'A')
    {
      True_OR_False(buffer.length());
      buffer = "";
    }
  }
}

void True_OR_False(int buffer_index)
{
  for(int i=0; i<buffer_index; i++) password.append(buffer[i]);
  
  if( password.evaluate()==1 )
  {
    Serial.println("Unlock!");
    /* Do something */
  }
  else if( password.evaluate()==0 )
  {
    Serial.println("Wrong passwords!");
  }
  password.reset();
}
