#include <BluetoothSerial.h>  //導入 Bluetooth 程式庫

BluetoothSerial BT;  //宣告 BT 為藍芽通訊物件
bool led_sw;
const int LED[5] = { 19, 18, 5, 17, 16 };
char var;
bool LED_state[7][5] = {
  { 0, 0, 0, 0, 0 },
  { 1, 0, 0, 0, 0 },
  { 0, 1, 0, 0, 0 },
  { 0, 0, 1, 0, 0 },
  { 0, 0, 0, 1, 0 },
  { 0, 0, 0, 0, 1 },
  { 1, 1, 1, 1, 1 },
};

void setup() {
  Serial.begin(9600);
  BT.begin("ESP32_2");  //設定藍芽名稱為 ESP32_組別號碼
  //宣告初始腳位及狀態
  for (int i = 0; i < 5; i++) {
    pinMode(LED[i], OUTPUT);
    digitalWrite(LED[i], LOW);
  }
}

void loop() {
  if (BT.available()) {
    //若收到藍牙終端的資料，則執行特定指令
    var = BT.read();
    if (var == '0') {
      for (int i = 0; i < 5; i++) {
        digitalWrite(LED[i], LOW);
      }
    } else if (var == '1') {
      for (int i = 0; i < 5; i++) {
        digitalWrite(LED[i], HIGH);
        delay(500);
        digitalWrite(LED[i], LOW);
      }
    } else if (var == '2') {
      for (int i = 5; i >= 0; i--) {
        digitalWrite(LED[i], HIGH);
        delay(500);
        digitalWrite(LED[i], LOW);
      }
    } else if (var == '3') {
      for (int i = 0; i < 5; i++) {
        digitalWrite(LED[i], HIGH);
      }
    } else {
      for (int i = 0; i < 5; i++) {
        digitalWrite(LED[i], HIGH);
      }
      delay(200);
      for (int i = 0; i < 5; i++) {
        digitalWrite(LED[i], LOW);
      }
      delay(200);
      for (int i = 0; i < 5; i++) {
        digitalWrite(LED[i], HIGH);
      }
      delay(200);
      for (int i = 0; i < 5; i++) {
        digitalWrite(LED[i], LOW);
      }
    }
  }
}