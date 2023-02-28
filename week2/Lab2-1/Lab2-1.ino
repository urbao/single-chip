const int Led[5] = {8, 9, 10, 11, 12};    //LED
const int sw_up = 2;    //按鈕1
const int sw_down = 3;    //按鈕2
int pos = 2;  //初始亮LED位置

void setup() {
  Serial.begin(9600);
  for(int i=0; i<5; i++){
    pinMode(Led[i], OUTPUT);
    digitalWrite(Led[i], LOW);
  }
  digitalWrite(Led[2], HIGH);
  pinMode(sw_up, INPUT_PULLUP);  //內建上拉電阻
  pinMode(sw_down,INPUT);
}

void loop() {
  bool swstate_up = digitalRead(sw_up);
  bool swstate_down = digitalRead(sw_down);
  if(swstate_up == LOW)
  {
    // 持續判斷開關狀態
    while(swstate_up == LOW)
    {
      swstate_up = digitalRead(sw_up);
    }
    digitalWrite(Led[pos], LOW);
    pos=(pos+1)%5;
    digitalWrite(Led[pos], HIGH);
    Serial.print("pos = ");
    Serial.println(pos);
  }
  if(swstate_down == HIGH)
  {
    // 持續判斷開關狀態
    while(swstate_down == HIGH)
    {
      swstate_down = digitalRead(sw_down);
    }
    digitalWrite(Led[pos], LOW);
    if(pos==0)
      pos = 4;
    else
      pos--;
    digitalWrite(Led[pos], HIGH);
    Serial.print("pos = ");
    Serial.println(pos);
  }
}
