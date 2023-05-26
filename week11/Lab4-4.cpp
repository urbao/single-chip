#include "mbed.h"

AnalogOut breathled(PA_4);
volatile float i = 0;
volatile float ctrl = 1;
Ticker breath_ticker;

void breath() {
  i = 0;
  ctrl = !ctrl;
}

int main(void) {
  breath_ticker.attach(&breath, 2.0);
  float x;
  while (1) {
    i += 0.1;
    if (ctrl == 1)
      x = ctrl - i;
    if (ctrl == 0)
      x = ctrl + i;
    breathled.write(x);
    wait(0.1);
  }
}