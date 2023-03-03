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
const int T = 100; // 取樣次數
const int dt = 15; // 間隔時間
int now_timer = 0, pre_timer = 0; // 計時器
int pos;
int count = 0, N = 0; // 計數器和目前取樣次數
const int16_t a_th = 32768 * 0.02 ;// 0.04g;
bool state; // 1: up, 0: down
bool pre_state; // 1: up, 0: down

const int SEG_COM[4] = {10, 11, 12, 13};  //控制線
const int LED[7] = {3, 4, 5, 6, 7, 8, 9}; //顯示器
const int SEG_data[10][8] =
{ {1, 1, 1, 1, 1, 1, 0, 0},  //"0"  //資料線
  {0, 1, 1, 0, 0, 0, 0, 0},  //"1"
  {1, 1, 0, 1, 1, 0, 1, 0},  //"2"
  {1, 1, 1, 1, 0, 0, 1, 0},  //"3"
  {0, 1, 1, 0, 0, 1, 1, 0},  //"4"
  {1, 0, 1, 1, 0, 1, 1, 0},  //"5"
  {1, 0, 1, 1, 1, 1, 1, 0},  //"6"
  {1, 1, 1, 0, 0, 0, 0, 0},  //"7"
  {1, 1, 1, 1, 1, 1, 1, 0},  //"8"
  {1, 1, 1, 0, 0, 1, 1, 0}}; //"9"
int disp[4]; //欲顯示數字

void setup()
{
  Serial.begin(115200);
  accelgyro.initialize();
  state = 0; // 1: up, 0: down
  pre_state = 0; // 1: up, 0: down
  for (int i = 3; i <= 13; i++)
  {
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
  }
  pos = 0;
  now_timer = 0;
  pre_timer = 0;
}

void loop()
{
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  dx = ax - nx;
  dy = ay - ny;
  dz = az - nz;
  if (N < T)// 取平均
  {
    nx += (ax / T);
    ny += (ay / T);
    nz += (az / T);
    N++;
  }
  if (N == T)
  {
    Serial.print("nx: ");
    Serial.print(nx);
    Serial.print("  ny: ");
    Serial.print(ny);
    Serial.print("  nz: ");
    Serial.println(nz);
    N++;
  }
  if (N > T)
  {
    if (now_timer > (pre_timer + dt))
    {
      pre_state = state; // 記錄前一次狀態
      pre_timer = now_timer; // 紀錄現在量測時間
      // 以z方向加速度判斷
      if (dz > a_th)
      {
        state = 1; // up
      }
      else if (dz < (-1 * a_th))
      {
        state = 0; // down
      }

      // 先向上再向下算一次
      if (pre_state != state && state == 0)
      {
        count++;
        Serial.print("count: ");
        Serial.println(count);
      }
    }
    now_timer++; // 現在量測時間+1
  }
  // 避免timer溢位，定時歸零
  if (now_timer > 5000)
  {
    now_timer = 0;
    pre_timer = 0;
  }

  // 顯示器控制訊號
  number_transfer(count);  //數值轉換入陣列中
  digitalWrite(SEG_COM[pos], LOW);  //觸發第i位數顯示數字
  SEG_Drive(disp[pos]);  //資料線寫入數值
  delay(5);
  digitalWrite(SEG_COM[pos], HIGH);  //結束觸發第i位數
  if (pos < 4)
    pos++;
  else
    pos = 0;
}

void SEG_Drive(int number) { //將字元變數從SEG_data[][]找到相對應的位置，並寫入a~g中
  for (int i = 0; i < 7; i++)
  {
    digitalWrite(LED[i], SEG_data[number][i]);
  }
}
void number_transfer(int Num) { //四位數拆成四個獨立的數字，存入陣列disp[]中
  disp[3] = Num / 1000;
  disp[2] = (Num / 100) % 10;
  disp[1] = (Num / 10) % 10;
  disp[0] = Num % 10;
}
