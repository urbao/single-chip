#include <Wire.h>
#include <LiquidCrystal_I2C.h>

int trigPin1 = 9, trigPin2 = 12;
int echoPin1 = 8, echoPin2 = 11;
int temperature = 20;
double velocity = (331.5 + 0.607 * temperature) * 100 / 1000000;
LiquidCrystal_I2C lcd(0x27, 16, 2);

long du1, cm1;
long du2, cm2;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);

  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

  lcd.init();  //設定lcd
  lcd.backlight();
  lcd.setCursor(0, 0);
}

void loop() {
  // ex.給 Trig1 高電位，持續 10微秒
  digitalWrite(trigPin1, HIGH);
  delay(0.01);
  digitalWrite(trigPin1, LOW);
  du1 = pulseIn(echoPin1, HIGH);  // 收到高電位時的時間

  delay(200);  //分開兩次取樣時間，避免干擾

  // ex.給 Trig2 高電位，持續 10微秒
  digitalWrite(trigPin2, HIGH);
  delay(0.01);
  digitalWrite(trigPin2, LOW);
  du2 = pulseIn(echoPin2, HIGH);  //收到高電位時的時間

  // 將時間換算成距離 cm 或 inch
  cm1 = (du1 * velocity) / 2;
  cm2 = (du2 * velocity) / 2;
  Serial.print("1: ");
  Serial.print(cm1);
  Serial.print("cm;  ");
  Serial.print("2: ");
  Serial.print(cm2);
  Serial.print("cm;  ");

  lcd.clear();

  // 判斷不同超音波到的距離關係，給定所屬區域
  if (cm1 < 10 && cm2 < 10) {
    Serial.println("Backup");
    lcd.setCursor(0, 0);
    lcd.print("Backup");
  } else if (cm1 >= 10 && cm1 < 20 && cm2 >= 10 && cm2 < 20) {
    Serial.println("Stop");
    lcd.setCursor(0, 0);
    lcd.print("Stop");
  } else if (cm1 >= 10 && cm1 < 20 && cm2 >=20) {
    Serial.println("Left");
    lcd.setCursor(0, 0);
    lcd.print("Left");
  } else if (cm1 >= 20 && cm2 >= 10 && cm2 < 20) {
    Serial.println("Right");
    lcd.setCursor(0, 0);
    lcd.print("Right");
  } else {
    Serial.println("Forward");
    lcd.setCursor(0, 0);
    lcd.print("Forward");
  }

  delay(10);
}