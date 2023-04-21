#include <Keypad.h>  //引用Keypad函式庫
#define KEY_ROWS 4   //按鍵模組的列數
#define KEY_COLS 4   //按鍵模組的行數
const byte colPins[4] = {13, 9, A4, A5};
const byte rowPins[4] = {A0, A1, A2, A3};
const char keymap[KEY_ROWS][KEY_COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};
Keypad myKeypad = Keypad(makeKeymap(keymap), rowPins, colPins, KEY_ROWS, KEY_COLS);
const int SEG_COM[3] = {10, 11, 12};  //控制線
const int SEG[7] = {2, 3, 4, 5, 6, 7, 8};                     //控制線
const int SEG_data[10][8] = { { 1, 1, 1, 1, 1, 1, 0, 0 },    //"0"  //資料線
                              { 0, 1, 1, 0, 0, 0, 0, 0 },    //"1"
                              { 1, 1, 0, 1, 1, 0, 1, 0 },    //"2"
                              { 1, 1, 1, 1, 0, 0, 1, 0 },    //"3"
                              { 0, 1, 1, 0, 0, 1, 1, 0 },    //"4"
                              { 1, 0, 1, 1, 0, 1, 1, 0 },    //"5"
                              { 1, 0, 1, 1, 1, 1, 1, 0 },    //"6"
                              { 1, 1, 1, 0, 0, 0, 0, 0 },    //"7"
                              { 1, 1, 1, 1, 1, 1, 1, 0 },    //"8"
                              { 1, 1, 1, 0, 0, 1, 1, 0 } };  //"9"

//your variable
int disp[3];  //顯示數字
int Num = 0;
volatile int pos = 0;  // index of disp[]
String buffer;
void setup() {
  Serial.begin(115200);
  //共陽極
  for (int i = 2; i <= 13; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);  //共陽極
  }
  // initialize timer1
  // disable all interrupts
  noInterrupts();
  // TCCR1A Reset
  TCCR1A = 0;
  // TCCR1B Reset
  TCCR1B = 0;
  // load timer
  TCNT1 = 0;
  // set compare value by OCR1?
  OCR1A = 1250;  // 16MHz/64/200Hz
  // 64 prescaler
  // set CTC mode by TCCR1?
  TCCR1B |= (1 << CS11);
  TCCR1B |= (1 << CS10);
  //enable  Timer1 compare interrupt mode by TIMSK?
  TIMSK1 |= (1 << OCIE1A);  // enable Outout Compare A Match Interrupt
  //enable  interrupt
  interrupts();
}

void loop() {
  //透過Keypad函式庫裡的getkey()方法讀取按鍵的字元
  char key = myKeypad.getKey();
  //TODO
  if (key >= 48 && key <= 57) {
    buffer = buffer + key;
    Serial.println(buffer);
  }
  if (key == '#') {
    //TODO
    Num = buffer.toInt();
    number_transfer(Num);
  }
  if (key == '*') {
    //TODO
    buffer = "";
  }
}
//200Hz
ISR(TIMER1_COMPA_vect) {
  //七段顯示不同位數的觸發、結束、資料線寫入數值
  //TODO
  TCNT1 = 0;
  digitalWrite(SEG_COM[pos], HIGH);  //結束觸發第i位數顯示數字
  pos = (pos + 1) % 3;
  digitalWrite(SEG_COM[pos], LOW);  //觸發第i位數顯示數字
  SEG_Drive(disp[pos]);             //資料線寫入數值
}
void number_transfer(int Num) {  //三位數拆成三個獨立的數字，存入陣列disp[]中
  //TODO
  disp[0] = Num % 10;
  disp[1] = (Num / 10) % 10;
  disp[2] = Num / 100;
}
void SEG_Drive(int number) {  //將字元變數從SEG_data[][]找到相對應的位置，並寫入a~g中
                              //TODO
  for (int i = 0; i < 8; i++) {
    digitalWrite(SEG[i], SEG_data[number][i]);
  }
}