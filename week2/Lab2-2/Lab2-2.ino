const int sw = 2;
const int LED = 13;
bool sw_state;
bool last_sw_state = LOW;
bool debounce_sw_state = LOW;
bool LED_state = LOW;
int counter = 0;
unsigned long debounce_timer;
const int debounce_delay = 50;
void setup() {
  Serial.begin(9600);
  pinMode(sw, INPUT);
  pinMode(LED, OUTPUT);
}

void loop() {
  sw_state = digitalRead(sw);
  if(sw_state != last_sw_state)
  {
    debounce_timer = millis();
  }
  if(millis() - debounce_timer >= debounce_delay)
  {
    if(sw_state != debounce_sw_state)
    {
      debounce_sw_state = sw_state;
      if(last_sw_state == LOW)
      {
        LED_state = !LED_state;
        counter = counter + 1;
        Serial.print("Click: ");
        Serial.print(counter);
        Serial.println(sw_state);
      }
    }
   }
  digitalWrite(LED, LED_state);
  last_sw_state = sw_state;
}
