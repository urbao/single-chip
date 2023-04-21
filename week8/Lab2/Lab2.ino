#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2); //設定LCD地址

volatile signed long time_all=0;
volatile signed long time_ms=0;
volatile signed long time_s=5;
volatile signed long time_min=0;
volatile signed long time_hr=0;

void setup(){
  Serial.begin(115200);
  lcd.init(); //初始化LCD
  lcd.backlight(); //開啟背光
  lcd.setCursor(0,1); //初始位置(1,0)
  lcd.print("00(sec):00(10ms)");
  lcd.setCursor(0,0);
  lcd.print("00(hr):00(min):");

  // sum up all time into ms unit
  time_all=(360000*time_hr)+(6000*time_min)+(100*time_s)+(1*time_ms);
    
  //TODO: initialize timer1
  noInterrupts();
  TCCR1A=0;
  TCCR1B=0;
  TCNT1=0;
  TCCR1B|=(1<<CS12);
  OCR1A=625;
  TIMSK1|=(1<<OCIE1A);
  interrupts();
}

void loop(){
  //TODO: your design
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print(String(time_s)+"(sec):"+String(time_ms)+"(10ms) ");
  lcd.setCursor(0,0);
  lcd.print(String(time_hr)+"(hr):"+String(time_min)+"(min): ");
}

ISR(TIMER1_COMPA_vect){
  //TODO:  your design
  TCNT1=0; // need to reset the Timer Counter
  if(time_all>0)time_all--;
  time_hr=time_all/360000;
  time_min=time_all/6000%60;
  time_s=time_all/100%60;
  time_ms=time_all%100;
}

