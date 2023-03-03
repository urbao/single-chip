#include <Wire.h>
#include <I2Cdev.h>
#include <MPU6050.h>
#include <math.h>

//MPU-6050設定
MPU6050 accelgyro;        // 預設 I2C 位址為 0x68
int16_t ax, ay, az, gx, gy, gz;

//全域變數設定
double nx = 0, ny = 0, nz = 0; // 平均值
double dx, dy, dz;
const int T = 1000; // 取樣次數
int time = 0;
int count = 0;
const int16_t a_th = 32768 * 0.01 ;// 0.02g;
bool state; // 1: up, 0: down
bool pre_state; // 1: up, 0: down

void setup()
{
  Serial.begin(115200);
  accelgyro.initialize();
  state = 0; // 1: up, 0: down
  pre_state = 0; // 1: up, 0: down
}

void loop()
{
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  dx = ax - nx;
  dy = ay - ny;
  dz = az - nz;
  if (time < T)
  {
    nx+=(ax/T);
    ny+=(ay/T);
    nz+=(az/T);
    time++;
    delay(1);
  }
  if(time == T) // 取平均
  {
    Serial.print("nx: ");
    Serial.println(nx);
    Serial.print("ny: ");
    Serial.println(ny);
    Serial.print("nz: ");
    Serial.println(nz);
    time++;
  }
  if (time > T)
  {
    pre_state = state;
    if(dz > a_th)
    {      
      state = 1; // up
    }
    else if(dz < (-1 * a_th))
    {
      state = 0; // down
    }
    delay(100); 
  }
  if(pre_state != state && state == 0)
  {
    count++;
    Serial.println(count);
  }
}
