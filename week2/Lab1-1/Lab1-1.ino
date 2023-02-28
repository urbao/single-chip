int Led[5] = {8, 9, 10, 11, 12};

void setup() {
  for(int i=0; i<5; i++)
    pinMode(Led[i], OUTPUT);
}

void loop() {
  bool direction = 1; // 1:right ；0:left
  if(direction == 1)
  {
    for(int i=0; i<5; i++)
    {
      digitalWrite(Led[i], HIGH);  //第8腳位輸出高電位，點亮LED
      delay(500);  //等待500ms
      digitalWrite(Led[i], LOW);  //第8腳位輸出低電位，熄滅LED
      delay(500);  //等待500ms
      if(i==4)
      direction = 0 ;
    }
  }
  if(direction == 0)
  {
    for(int i=4; i>=0; i--)
    {
      digitalWrite(Led[i], HIGH);  //第8腳位輸出高電位，點亮LED
      delay(500);  //等待500ms
      digitalWrite(Led[i], LOW);  //第8腳位輸出低電位，熄滅LED
      delay(500);  //等待500ms
      if(i==0)
      direction = 1 ;
    }
  }
}
