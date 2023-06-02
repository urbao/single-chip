
/*
請利用上述 RTOS 中的 Signals 來控制開發版的LED：※必須以Signals觸發Thread
輸入"1"，亮綠燈。
輸入"2"，亮藍燈。
輸入"3"，亮紅燈。
*/

#include "mbed.h"
#include "rtos.h"
char w;
DigitalOut led[3] = {LED1, LED2, LED3};
Thread a;
Thread b;
Thread c;

// 輸入"1"，亮綠燈
void mode1() {
  while (true) {
    // Signal flags that are reported as event are automatically cleared.
    a.signal_wait(0x1);
    led[0] = 1;
    led[1] = 0;
    led[2] = 0;
  }
}

// 輸入"2"，亮藍燈。
void mode2() {
  while (true) {
    // Signal flags that are reported as event are automatically cleared.
    b.signal_wait(0x1);
    led[0] = 0;
    led[1] = 1;
    led[2] = 0;
  }
}

// 輸入"3"，亮紅燈。
void mode3() {
  while (true) {
    // Signal flags that are reported as event are automatically cleared.
    c.signal_wait(0x1);
    led[0] = 0;
    led[1] = 0;
    led[2] = 1;
  }
}

int main() {
  Serial pc(SERIAL_TX, SERIAL_RX);
  a.start(callback(mode1));
  b.start(callback(mode2));
  c.start(callback(mode3));
  while (true) {
    if (pc.readable()) {
      w = pc.getc();
      if (w == '1'){
        a.signal_set(0x1);
      }
      else if (w == '2'){
        b.signal_set(0x1);
      }
      else if (w == '3'){
        c.signal_set(0x1);
      }
    }
  }
}
