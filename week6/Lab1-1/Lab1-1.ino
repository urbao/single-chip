#include <BluetoothSerial.h>  //導入 Bluetooth 程式庫

BluetoothSerial BT;  //宣告 BT 為藍芽通訊物件
bool led_sw;
const int LED = 19;
char var;  //儲存接收到的資料變數

void setup() {
  Serial.begin(9600);
  BT.begin("ESP32_2");  //設定藍芽名稱為 ESP32_組別號碼
  //宣告初始腳位及狀態
  pinMode(LED, OUTPUT);
  led_sw = LOW;
}

void loop() {
  if (BT.available()) {
    //若收到藍牙終端的資料，則執行特定指令
    var = BT.read();

    if (var == '0') {
      digitalWrite(LED, HIGH);
      Serial.println(var);
    } else if (var == '1') {
      digitalWrite(LED, LOW);
      Serial.println(var);
    } else {
      Serial.println(var);
      for (int i = 0; i < 2; i++) {
        digitalWrite(LED, LOW);
        delay(200);
        digitalWrite(LED, HIGH);
        delay(200);
      }
    }
  }
  /*switch (var) {
    case '0':
      digitalWrite(LED, HIGH);
      Serial.println(var);
      break;
    case '1':
      digitalWrite(LED, LOW);
      Serial.println(var);
      break;
    default:
      Serial.println(var);
      for (int i = 0; i < 2; i++) {
        digitalWrite(LED, LOW);
        delay(200);
        digitalWrite(LED, HIGH);
        delay(200);
      }
      break;
  }*/
}