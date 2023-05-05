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

  imu.Config(&Wire, bfs::Mpu9250::I2C_ADDR_PRIM);

  if (!imu.Begin()) {
    Serial.println("Error initializing communication with IMU");
    Serial.println(imu.Begin());
    while (1) {};
  } else {
    Serial.println("success initializing communication with IMU");
  }
}

void loop() {
  /* Check if data read */
  float gx, gy, gz, ax, ay, az, mx, my, mz;

  if (imu.Read()) {
    if (imu.new_imu_data()) {
      Serial.print(ax = imu.accel_x_mps2());
      Serial.print("\t");
      Serial.print(ay = imu.accel_y_mps2());
      Serial.print("\t");
      Serial.print(az = imu.accel_z_mps2());
      Serial.print("\t");
      Serial.print(gx = imu.gyro_x_radps());
      Serial.print("\t");
      Serial.print(gy = imu.gyro_y_radps());
      Serial.print("\t");
      Serial.print(gz = imu.gyro_z_radps());
      Serial.print("\t");
      Serial.print(mx = imu.mag_x_ut());
      Serial.print("\t");
      Serial.print(my = imu.mag_y_ut());
      Serial.print("\t");
      Serial.print(mz = imu.mag_z_ut());
      Serial.print("\n");
    }
  }
}