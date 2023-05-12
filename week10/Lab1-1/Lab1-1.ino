#include <WiFi.h>               //Wi-Fi 程式庫
#include <Wire.h>               //I2C 程式庫
#include <LiquidCrystal_I2C.h>  //LCD_I2C 模組程式庫

LiquidCrystal_I2C lcd(0x27, 16, 2);

const char* ssid = "QAQ";                //Wi-Fi 網路名稱
const char* password = "E24b46435298";   //Wi-Fi 密碼
const char* ntpServer = "pool.ntp.org";  //校時伺服器
const long gmtOffset_sec = 8 * 3600;     //格林威治時間, GMT+8 就是 8*3600
const int daylightOffset_sec = 0;        //日光調節時間, 有為 3600, 沒有則為 0

void setup() {
  Serial.begin(115200);

  //初始化LCD
  //To do.
  lcd.init();
  lcd.backlight();
  //Connect to Wi-Fi
  //To do.
  WiFi.mode(WIFI_STA);  //設置 Wi-Fi 模式
  WiFi.begin(ssid, password);

  Serial.print("Wi-Fi Connecting");
  lcd.setCursor(0, 0);
  lcd.print("Wi-Fi Connecting");

  //當 Wi-Fi 連線時會回傳 WL_CONNECTED，因此跳出迴圈時代表已成功連線
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.print("Wi-Fi Connected.");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Wi-Fi Connecting");
  //取得網路時間
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime();

  //連上拿到時間資料後就切斷連線
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
  lcd.clear();
}

void loop() {
  delay(1000);
  printLocalTime();
}

void printLocalTime() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");

  //顯示於 LCD 螢幕
  //To do.
  lcd.setCursor(0, 0);  // 從(col,row)開始顯示
  lcd.print(&timeinfo, "%Y %B %d");
  lcd.setCursor(0, 1);
  lcd.print(&timeinfo, "%H:%M:%S");
}