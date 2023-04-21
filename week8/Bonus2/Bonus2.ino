#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/wdt.h>

int LED_PIN = 13;  //TODO

//variable setting
volatile int state = 1;

ISR(WDT_vect) {
  // your design
  if (state == 0) {
    state = 1;
  } else {
    Serial.println("WDT Overrun!!!");
  }
}

void into_sleep_mode() {
  set_sleep_mode(SLEEP_MODE_PWR_SAVE);  //設定睡眠模式

  sleep_enable();  //啟用睡眠模式

  sleep_mode();  //進入前面設定的睡眠模式，等待定時器或外部中斷觸發

  //收到watchdog定時器的中斷被觸發而喚醒，並繼續執行之前睡眠前的程序。
  sleep_disable();  //關閉睡眠模式

  power_all_enable();  //重新啟用周邊設備，讓MCU可以繼續執行程序。
}

void setup() {
  Serial.begin(9600);
  Serial.println("Initializing...");
  delay(100);  //Allow for serial print to complete.

  pinMode(13, OUTPUT);

  MCUSR &= ~(1 << WDRF);  //清除reset flag,以確保WDT在進入睡眠模式前不會重置

  WDTCSR |= (1 << WDCE) | (1 << WDE);  //設定WDCE和WDE，以便可以更改WDTCSR 的設置。

  WDTCSR = (1 << WDP3);  //TODO  //prescale設定，請根據題目的秒數做，每4秒觸發一次

  WDTCSR |= _BV(WDIE);  //啟用WDT的中斷。我們不設定重置微控制器，只使用中斷服務程序


  Serial.println("Initialisation complete.");
  Serial.println("111");
  delay(100);  //Allow for serial print to complete.
}


void loop() {
  // your design
  if (state == 1) {
    digitalWrite(13, !digitalRead(13));
    state = 0;
    into_sleep_mode();
  }
}
