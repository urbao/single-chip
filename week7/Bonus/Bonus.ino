int in1 = 2, in2 = 4;
int in3 = 5, in4 = 6;
int enA = 3, enB = 10;

int trigPin_left = 9, trigPin_right = 12;
int echoPin_left = 8, echoPin_right = 11;
int temperature = 20;
double velocity = (331.5 + 0.607 * temperature) * 100 / 1000000;

long du_left, cm_left;
long du_right, cm_right;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin_left, OUTPUT);
  pinMode(echoPin_left, INPUT);

  pinMode(trigPin_right, OUTPUT);
  pinMode(echoPin_right, INPUT);

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
  // ex.給 Trig1 高電位，持續 10微秒
  digitalWrite(trigPin_left, HIGH);
  delay(0.01);
  digitalWrite(trigPin_left, LOW);
  du_left = pulseIn(echoPin_left, HIGH);  // 收到高電位時的時間

  delay(200);  //分開兩次取樣時間，避免干擾

  // ex.給 Trig2 高電位，持續 10微秒
  digitalWrite(trigPin_right, HIGH);
  delay(0.01);
  digitalWrite(trigPin_right, LOW);
  du_right = pulseIn(echoPin_right, HIGH);  //收到高電位時的時間

  // 將時間換算成距離 cm 或 inch
  cm_left = (du_left * velocity) / 2;
  cm_right = (du_right * velocity) / 2;

  // 判斷不同超音波到的距離關係，給定所屬區域
  if (cm_left < 5 && cm_right < 5) {
    Serial.println("Backup");
    A_cclock();
    B_cclock();
  } else if (cm_left >= 5 && cm_left < 10 && cm_right >= 5 && cm_right < 10) {
    Serial.println("Backup");
    A_clock();
    B_cclock();
  } else if (cm_left >= 20 && cm_right >= 20) {
    Serial.println("Forword");
    A_clock();
    B_clock();
  } else if (cm_left >= 10 && cm_left < 20 && cm_right >= 20) {
    Serial.println("Turn Right");
    A_clock();
    B_stop();
  } else if (cm_left >= 20 && cm_right >= 10 && cm_right < 20) {
    Serial.println("Turn Left");
    A_stop();
    B_clock();
  }

  delay(10);
}

void A_clock() {
  //A順時針
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
}
void B_clock() {
  //B順時針
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}
void A_cclock() {
  //A逆時針
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
}
void B_cclock() {
  //B逆時針
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}
void A_stop() {
  //A停止
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
}
void B_stop() {
  //B停止
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}