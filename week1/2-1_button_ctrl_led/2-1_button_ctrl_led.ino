const int Led[5] = {8, 9, 10, 11, 12};    // All LED pin number
const int sw_up = 2;    // Button 1 pin number for pull-up swtich
const int sw_down = 3;    // Button 2 for pull-down switch
int pos = 2;  // Initally, the LED at pos index turns on

void setup() {
  for(int i=0; i<5; i++){
    pinMode(Led[i], OUTPUT);
    digitalWrite(Led[i], LOW);
  }
  digitalWrite(Led[2], HIGH); // turn on the default LED
  pinMode(sw_up, INPUT_PULLUP);  // Built-in pull-up resistance
  pinMode(sw_down,INPUT);
}

void loop() {
  bool swstate_up = digitalRead(sw_up);
  bool swstate_down = digitalRead(sw_down);
    // Since LOW means the pull-up switch is pressed down
    // so, need to take action to control LED
  if(swstate_up==LOW){
    // action: turn off the current LED, and turn on the left LED 
    digitalWrite(Led[pos], LOW); // turn off the current LED
    // make some check for possible error(invalid LED index)
    if(pos==0)pos=4;
    else pos=pos-1;
    digitalWrite(Led[pos], HIGH); // turn on the corresponding LED
  }
    // Since HIGH means the pull-down switch is pressed down
    // so, need to take action to control LED
  else if(swstate_down==HIGH){
    // action: turn off the current LED, and turn on the right LED 
    digitalWrite(pos, LOW); // turn off the current LED
    // make some check for possible error(invalid LED index)
    if(pos==4)pos=0;
    else pos=pos+1;
    digitalWrite(Led[pos], HIGH); // turn on the corresponding LED

  }
}
