#include <BluetoothSerial.h>  //導入 Bluetooth 程式庫

BluetoothSerial BT;  //宣告 BT 為藍芽通訊物件
char var;

const int SEG_COM[4] = { 12, 18, 5, 4 };                     //控制線
const int SEG[8] = { 16, 19, 27, 25, 33, 17, 14, 26 };       //資料線
const int SEG_data[10][8] = { { 1, 1, 1, 1, 1, 1, 0, 0 },    //"0"
                              { 0, 1, 1, 0, 0, 0, 0, 0 },    //"1"
                              { 1, 1, 0, 1, 1, 0, 1, 0 },    //"2"
                              { 1, 1, 1, 1, 0, 0, 1, 0 },    //"3"
                              { 0, 1, 1, 0, 0, 1, 1, 0 },    //"4"
                              { 1, 0, 1, 1, 0, 1, 1, 0 },    //"5"
                              { 1, 0, 1, 1, 1, 1, 1, 0 },    //"6"
                              { 1, 1, 1, 0, 0, 0, 0, 0 },    //"7"
                              { 1, 1, 1, 1, 1, 1, 1, 0 },    //"8"
                              { 1, 1, 1, 0, 0, 1, 1, 0 } };  //"9"
int disp[4];
int pos = 0;  //顯示數字
int number = 0;
bool start = false;
long pretime = 0;
unsigned long curtime = 0;
unsigned long timer = 0;

void setup() {
  Serial.begin(9600);
  BT.begin("ESP32_2");  //設定藍芽名稱為 ESP32_組別號碼
  //宣告初始腳位及狀態
  for (int i = 0; i < 4; i++) {
    pinMode(SEG_COM[i], OUTPUT);
    digitalWrite(SEG_COM[i], HIGH);
  }
  for (int i = 0; i < 8; i++) {
    pinMode(SEG[i], OUTPUT);
    digitalWrite(SEG_COM[i], HIGH);
  }
}

void loop() {
  if (BT.available()) {
    //若收到藍牙終端的資料，則執行特定指令
    var = BT.read();
    if (var == '1') {
      if (start == 1)
        start = 0;
      else
        start = 1;
    }
    if (var == '0') {
      start = false;
      number = 0;
    }
  }
  if (start) {

    curtime = millis();
    if (curtime >= pretime + 100) {
      number++;
      pretime = curtime;
    }
  }

  // 顯示器控制訊號
  number_transfer(number);          //數值轉換入陣列中
  digitalWrite(SEG_COM[pos], LOW);  //觸發第i位數顯示數字
  SEG_Drive(disp[pos]);             //資料線寫入數值
  Serial.println(pos);
  if (millis() >= timer + 5) {
    digitalWrite(SEG_COM[pos], HIGH);  //結束觸發第i位數
    timer = millis();
    if (pos == 3)
      pos = 0;
    else
      pos++;
  }
}


void SEG_Drive(int number) {  //將字元變數從SEG_data[][]找到相對應的位置，並寫入a~g中
  for (int i = 0; i < 8; i++) {
    digitalWrite(SEG[i], SEG_data[number][i]);
  }
}
void number_transfer(int Num) {  //四位數拆成四個獨立的數字，存入陣列disp[]中
  disp[3] = Num / 1000;
  disp[2] = (Num / 100) % 10;
  disp[1] = (Num / 10) % 10;
  disp[0] = Num % 10;
}