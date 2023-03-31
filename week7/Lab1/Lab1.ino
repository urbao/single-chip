int trigPin = 12;                  //Trig Pin
int echoPin = 11;                  //Echo Pin
long duration, cm, inches;
 
void setup() {
  Serial.begin (9600);             // Serial Port begin
  pinMode(trigPin, OUTPUT);        // 定義輸入及輸出 
  pinMode(echoPin, INPUT);
}
 
void loop()
{
  // ex.給 Trig 高電位，持續 10微秒
  digitalWrite(trigPin, HIGH);
  delay(0.01);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);   // 收到高電位時的時間
 
  // 將時間換算成距離 cm 或 inch
  cm=duration/2*0.034364;
  inches=0.393708*cm; 

  Serial.print("Distance : ");
  Serial.print(inches);
  Serial.print("in,   ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  
  delay(250);
}