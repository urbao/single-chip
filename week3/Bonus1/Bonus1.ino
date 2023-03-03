#include <Keypad.h>   //引用Keypad函式庫
#define KEY_ROWS 4    //按鍵模組的列數
#define KEY_COLS 4    //按鍵模組的行數

//Keypad設定
const byte colPins[4] = {13, 9, A4, A5};
const byte rowPins[4] = {A0, A1, A2, A3};
const char keymap[KEY_ROWS][KEY_COLS] = { {'1','2','3','A'}, 
                                          {'4','5','6','B'}, 
                                          {'7','8','9','C'},
                                          {'*','0','#','D'} };
const int SEG_COM[3] = {10, 11, 12};  //控制線
const int LED[7] = {2, 3, 4, 5, 6, 7, 8};
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

int disp[3];  //欲顯示數字

Keypad myKeypad = Keypad(makeKeymap(keymap),rowPins,colPins,KEY_ROWS,KEY_COLS);

//全域變數設定
String password = "2001";
String num_p = "";
char num_c[3];
String buffer = "";
bool operation = 0; // 判斷要輸入密碼還是修改密碼
bool verify = 0; // 驗證碼是否正確


void setup()
{  
  Serial.begin(9600);
  randomSeed(analogRead(0));
  // keypad pinMode
  for( int i=0; i<4; i++)
  {
    pinMode(colPins[i], INPUT);
    pinMode(rowPins[i], INPUT);
  }
  // 控制線 pinMode
  for( int i=0; i<3; i++)
  {
    pinMode(SEG_COM[i], OUTPUT);
    digitalWrite(SEG_COM[i], HIGH); // 共陽極
  }
  // 顯示器LED pinMode
  for( int i=0; i<7; i++)
  {
    pinMode(LED[i], OUTPUT);
    digitalWrite(LED[i], HIGH); // 共陽極
  }
  Serial.println();
  Serial.println("<輸入密碼>");
  Serial.println("<修改密碼> 請按'*'");
}

void loop()
{
  //輸入操作
  char key = myKeypad.getKey();
  if(key)
  {
    if(key == '*') // 修改密碼
    {
      Serial.println("<修改密碼>");
      Serial.println("<輸入驗證碼>");
      operation = 1;
      verify = 0;
      buffer = "";
      number_transfer(random(999));  //數值轉換入陣列中
      num_p = num_c; // 重置驗證碼
    }
    // 輸入數字
    if(key != '*') 
    {    
      if(operation == 0) // 輸入密碼
      {
        if(key >= 48 && key <= 57)
        {
          buffer = buffer + key;
          Serial.println("input: " + buffer);
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
          if(buffer == password)
            Serial.println("Unlock!");
          else
            Serial.println("Wrong passwords!");
          buffer = "";
        }
      }
      if(operation == 1) // 修改密碼
      {
        if(verify == 0)
        {
          if(key >= 48 && key <= 57)
          {
            buffer = buffer + key;
            Serial.println("input: " + buffer);
          }
          else if(key != 'A')
          {
            Serial.println("Illegal input!! Please input again.");
            Serial.println("");
            buffer = ""; 
          }
          //判斷驗證碼正確性
          if(key == 'A')
          {
            if(buffer == num_c)
              {
                verify = 1; // 驗證碼正確
                Serial.println("驗證碼正確!");
                Serial.println("<輸入新密碼>");
              }
            else 
              {
                verify = 0; // 驗證碼錯誤
                Serial.println("驗證碼錯誤!");          
              }
            buffer = "";
            number_transfer(random(999));  //數值轉換入陣列中
            num_p = num_c; // 重置驗證碼
          }                
        }
        else
        {
          if(key >= 48 && key <= 57)
          {
            buffer = buffer + key;
            Serial.println("input: " + buffer);
          }
          else if(key != 'A')
          {
            Serial.println("Illegal input!! Please input again.");
            Serial.println("");
            buffer = ""; 
          }
          if(key == 'A')
          {
            password = buffer; // 設定新密碼
            Serial.println("修改成功!");
            buffer = "";
            operation = 0;
            Serial.println();
            Serial.println("<輸入密碼>");
            Serial.println("<修改密碼> 請按'*'");
          }
        }
      }
    }
  }
  // 顯示器
  for(int i=0; i<3; i++){  //個、十、百位數
    digitalWrite(SEG_COM[i], LOW);  //觸發第i位數顯示數字
    SEG_Drive(disp[i]);  //資料線寫入數值
    delay(5);
    digitalWrite(SEG_COM[i], HIGH);  //結束觸發第i位數
  }
}

void number_transfer(int num){  //四位數拆成四個獨立的數字，存入陣列disp[]中
  disp[0]= num%10;
  disp[1]= (num/10)%10;
  disp[2]= num/100;
  num_c[0] = disp[2]+48; // 百位
  num_c[1] = disp[1]+48; // 十位
  num_c[2] = disp[0]+48; // 個位
}

void SEG_Drive(int number){  //將字元變數從SEG_data[][]找到相對應的位置，並寫入a~g中
  for(int i=0; i<7; i++)
  {
    digitalWrite(LED[i],SEG_data[number][i]);
  }
}
