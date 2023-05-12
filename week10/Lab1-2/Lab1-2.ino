#include <WiFiClient.h>            //WiFi 程式庫
#include <Wire.h>                  // I2C 程式庫
#include <TridentTD_LineNotify.h>  //Line 程式庫
#include "DHT.h"                   // DHT11 程式庫

#define LINE_TOKEN "MZu8H3RbOySZYyq76Mgpe5BpahBQzqsWH30vXEetbaZ"  //修改成上述的 Token 號碼
#define DHTTYPE DHT11
#define DHTPIN 23

const char* ssid = "QAQ";               //Wi-Fi 網路名稱
const char* password = "E24b46435298";  //Wi-Fi 密碼

float humidity, temp_c;  //從 DHT11 讀取的值

DHT dht(DHTPIN, DHTTYPE);  //啟動 DHT 程式庫

void setup() {
  Serial.begin(115200);
  dht.begin();

  // Connect to Wi-Fi
  // To do.
  WiFi.mode(WIFI_STA);  //設置 Wi-Fi 模式
  WiFi.begin(ssid, password);

  Serial.print("Wi-Fi Connecting");

  //當 Wi-Fi 連線時會回傳 WL_CONNECTED，因此跳出迴圈時代表已成功連線
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.print("Wi-Fi Connected.");

  Serial.println(LINE.getVersion());  //顯示 Line 版本
  LINE.setToken(LINE_TOKEN);          //設定要傳送至的聊天室 Token
}

void loop() {
  //讀取環境溫濕度
  temp_c = dht.readTemperature();  //讀取溫度(攝氏)
                                   //To do.
  humidity = dht.readHumidity();   //讀取濕度
  Serial.printf("Temperature: %f \n", temp_c);
  Serial.printf("Humidity: %f \n", humidity);

  //傳送至 Token 的聊天室
  //To do.
  LINE.notify("Temperature: " + String(temp_c) + "*C \n Humidity: " + String(humidity) + "%");
  delay(1000);
}