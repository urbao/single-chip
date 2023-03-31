#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define led 3

int trigPin = 12;int echoPin = 11;
LiquidCrystal_I2C lcd(0x27, 16, 2);

long duration, cm, inches;

void setup() {
  Serial.begin (9600);
  pinMode (trigPin, OUTPUT);
  pinMode (echoPin, INPUT);
  pinMode (led, OUTPUT);
  
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
}

void loop() {
  // ex.給 Trig 高電位，持續 10微秒
  digitalWrite(trigPin, HIGH);
  delay(0.01);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);   // 收到高電位時的時間
 
  // convert the duration to distance cm and inches
  cm=duration/2*0.034364;

  if(cm < 50) {
    //把測得的距離，轉換為pwm值，輸出給led
    int PWM=(50-cm)*255/50;
    analogWrite(led, PWM);
  }
  
  //把測得的距離，輸出給lcd 
  lcd.setCursor(3, 0);
  lcd.print("Distance:");
  lcd.setCursor(3, 1);
  lcd.print(cm);
  lcd.print(" cm");
  delay(100);
  lcd.clear();
}
