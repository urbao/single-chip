#include <Adafruit_SSD1331.h>  //ssd1331 oled函式庫

//設定spi腳位
#define sck 14   //CLK
#define mosi 13  //DIN
#define cs 17
#define reset 15
#define dc 16

// 宣告ssd1331物件
Adafruit_SSD1331 oled =
  Adafruit_SSD1331(
    cs,
    dc,
    mosi,
    sck,
    reset);

//定義顏色
const uint16_t OLED_Color_Black = 0x0000;
const uint16_t OLED_Color_White = 0xFFFF;

void setup() {
  //oled基礎設定
  oled.begin();                         //初始化
  oled.setFont();                       //設定字型
  oled.fillScreen(OLED_Color_Black);    //底色為黑
  oled.setTextColor(OLED_Color_White);  //文字顏色為白
  oled.setTextSize(1);                  //設定文字大小
  oled.setTextWrap(false);              //不要自動換行
}
int i = 0;
void loop() {

  oled.setCursor(i-74, 0);                 //設定文字位址
  oled.setTextColor(OLED_Color_White);  //文字顏色為白
  oled.print("Hello World!");           //印出文字
  delay(10);
  oled.setCursor(i-74, 0);                 //設定文字位址
  oled.setTextColor(OLED_Color_Black);  //文字顏色為黑
  oled.print("Hello World!");           //印出文字

  i = (i+1) % 170;
}