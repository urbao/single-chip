#define in1 2
#define in2 4
#define in3 5
#define in4 6
#define enA 11
#define enB 10

void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);

  analogWrite(enA, 100);
  analogWrite(enB, 100);
}

void loop() {
  //每顆輪子按照順序輪流轉動
  A_clock();
  delay(1000);
  B_clock();
  delay(1000);
  A_stop();
  delay(1000);
  B_stop();
  delay(1000);
  A_cclock();
  delay(1000);
  B_cclock();
  delay(1000);
  A_stop();
  delay(1000);
  B_stop();
  delay(1000);
}

void A_clock() {
  //A順時針
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
void B_clock() {
  //B順時針
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}
void A_cclock() {
  //A逆時針
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
void B_cclock() {
  //B逆時針
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}
void A_stop() {
  //A停止
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
void B_stop() {
  //B停止
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
