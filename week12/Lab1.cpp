
/*
每隔１秒亮一顆LED，總共８顆輪流。
當開發板上 Button 按下後，每隔１秒同時亮兩顆LED。
再按一次開發板上的 Button 後，每隔１秒亮一顆LED且每隔0.5秒亮一顆LED(同時)。
在按一次 Button 後，LED燈全部閃爍。
最後再按一次Button回歸每隔１秒亮一顆LED的狀態
*/

#include "mbed.h"
#include "rtos.h"

DigitalIn but(USER_BUTTON);
DigitalOut led[5] = {D6, D7, D8, D9, D10};
int state = 0;
int j = 0;
int i = 0;
int x;
char w;
Thread a;
Thread b;
Thread c;
Thread d;

void mode1() // 每隔１秒亮一顆LED，總共８顆輪流
{
  while (1) {
    if (state == 0) {
      led[i] = 1;
      ThisThread::sleep_for(1000);
      led[i] = 0;
      i = (i + 1) % 5;
    }
  }
}

void mode2() // 每隔１秒同時亮兩顆LED
{
  while (1) {
    if (state == 1) {
      j = (i + 1) % 5;
      led[i] = 1;
      led[j] = 1;
      ThisThread::sleep_for(1000);
      led[i] = 0;
      led[j] = 0;
      i = (i + 1) % 5;
    }
  }
}

void mode3() // 每隔１秒亮一顆LED(i) & 每隔0.5秒亮一顆LED(j)
{
  while (1) {
    if (state == 2) {
      // i, j 同時亮
      led[i] = 1;
      led[j] = 1;
      ThisThread::sleep_for(500);
      // j 切換
      led[j] = 0;
      j = (j + 1) % 5;
      led[j] = 1;
      ThisThread::sleep_for(500);
      // i, j 切換
      led[i] = 0;
      led[j] = 0;
      i = (i + 1) % 5;
      j = (j + 1) % 5;
    }
  }
}

void mode4() // LED燈全部閃爍
{
  while (1) {
    if (state == 3) {
      led[0] = 1;
      led[1] = 1;
      led[2] = 1;
      led[3] = 1;
      led[4] = 1;
      wait_ms(1000);
      led[0] = 0;
      led[1] = 0;
      led[2] = 0;
      led[3] = 0;
      led[4] = 0;
      wait_ms(1000);
    }
  }
}

int main() {
  Serial pc(SERIAL_TX, SERIAL_RX);
  while (1) {
    if (but == 1) {
      state = (state + 1) % 4;
      printf("state = %d\r\n", state);
      wait_ms(500);
      while(but == 1){};
    }
    a.start(mode1);
    b.start(mode2);
    c.start(mode3);
    d.start(mode4);
  }
}
