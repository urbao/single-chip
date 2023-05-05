#include "mpu9250.h"
// SCL 22
// SDA 21
/* Mpu9250 object */
bfs::Mpu9250 imu;

void setup() {
  //開啟序列埠，鮑率115200
  Serial.begin(115200);
  //開啟I2C
  Wire.begin();
  Wire.setClock(400000);  //設定時脈
  //I2C匯流排，位址0x68
  imu.Config(&Wire, bfs::Mpu9250::I2C_ADDR_PRIM);
  //初始化mpu9250
  if (!imu.Begin()) {
    Serial.println("Error initializing communication with IMU");
    while (1) {}
  }
}
void loop() {
  /* Check if data read */
  float gx, gy, gz, ax, ay, az, mx, my, mz;

  if (imu.Read()) {
    if (imu.new_mag_data()) {
      Serial.print(mx = imu.mag_x_ut());
      Serial.print(",");
      Serial.print(my = imu.mag_y_ut());
      Serial.print(",");
      Serial.print(mz = imu.mag_z_ut());
      Serial.print("\n");
    }
  }
}