#include <Wire.h> // I2C程式庫
#include <LiquidCrystal_I2C.h> // LCD_I2C模組程式庫

LiquidCrystal_I2C lcd(0x27, 16, 2);// LCD I2C位址，默認為0x27或0x3F，依據背板的晶片不同而有差異，16、2為LCD顯示器大小。 


void setup() {
  lcd.init();
  lcd.backlight();
}
void loop() {
  lcd.setCursor(3, 0); // 在LCD第一排上顯示
  lcd.print("Hello World!");
  lcd.setCursor(3, 1); // move cursor to column 3, row 1
  lcd.print("Second Group");
}
