const int button = 2;
const int led = 13;  //UNO Built-in LED
bool led_state = HIGH;
bool tick_led_state = HIGH;

void setup() {
  pinMode(button, INPUT_PULLUP);  // Pull-up switch (1: No pressed, 0: pressed)
  pinMode(led, OUTPUT);
  digitalWrite(led, led_state);
  digitalWrite(tick_led, tick_led_state);
}

void loop() {
  if(digitalRead(button)==HIGH){  // Button not pressed
    //
  }
  else if(digitalRead(button)!=HIGH){  // Button pressed
  }

}
