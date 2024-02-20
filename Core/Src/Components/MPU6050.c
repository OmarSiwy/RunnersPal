#include "Components/MPU6050.h"

uint8_t ADDRESS = 0x68;
I2C_HandleTypeDef* I2C = &hi2c1;
bool LowerPowerMode = false;

static void _Initialize() {
    uint8_t check;
    HAL_I2C_Mem_Read(I2C, ADDRESS << 1, WHO_AM_I, 1, &check, 1, 100);
    if (check != ADDRESS) return;

    // Set Power Management Mode
    uint8_t Power2 = LowerPowerMode ? 0b00111111 : 0;
    uint8_t Power1 = 0b00000000;
    HAL_I2C_Mem_Write(I2C, ADDRESS << 1, PWR_MGMT_1, 1, &Power1, 1, 100);
    HAL_I2C_Mem_Write(I2C, ADDRESS << 1, PWR_MGMT_2, 1, &Power2, 1, 100);

    // Disable FIFO
    HAL_I2C_Mem_Write(I2C, ADDRESS << 1, FIFO_EN, 1, 0, 1, 100); // Turns off FIFO Buffer
    // Setup Sample Rate
    uint8_t SampleRate = SAMPLE_RATE;
    HAL_I2C_Mem_Write(I2C, ADDRESS << 1, SMPLRT_DIV, 1, &SampleRate, 1, 100); // Sample Rate = Gyroscope Output Rate / (1 + SMPLRT_DIV)
    // Config Acceleroemter and Gyroscope
    HAL_I2C_Mem_Write(I2C, ADDRESS << 1, ACCEL_CONFIG, 1, 0, 1, 100); // Set Bit 3-4 as 0 for range of +/- 2g
    HAL_I2C_Mem_Write(I2C, ADDRESS << 1, GYRO_CONFIG, 1, 0, 1, 100); // Set Bit 3-4 as 0 for Range for +/- 250 degrees/s
}

static double* ReadGyro(void) {
  uint8_t GyroData[6];
  HAL_I2C_Mem_Read(I2C, ADDRESS << 1, GYRO_XOUT_H, 1, GyroData, 6, 100);
  static double gyroValues[3];
  gyroValues[0] = (double)(GyroData[0] << 8 | GyroData[1]) / GyroLSBSensitivity;
  gyroValues[1] = (double)(GyroData[2] << 8 | GyroData[3]) / GyroLSBSensitivity;
  gyroValues[2] = (double)(GyroData[4] << 8 | GyroData[5]) / GyroLSBSensitivity;
  return gyroValues;
}

static double* ReadAccel(void) {
  uint8_t AccelData[6];
  HAL_I2C_Mem_Read(I2C, ADDRESS << 1, ACCEL_XOUT_H, 1, AccelData, 6, 100);
  static double accelValues[3];
  accelValues[0] = (double)(AccelData[0] << 8 | AccelData[1]) / AccelLSBSensitivity;
  accelValues[1] = (double)(AccelData[2] << 8 | AccelData[3]) / AccelLSBSensitivity;
  accelValues[2] = (double)(AccelData[4] << 8 | AccelData[5]) / AccelLSBSensitivity;
  return accelValues;
}

static double ReadTemp(void) {
  uint8_t TempData[2];
  HAL_I2C_Mem_Read(I2C, ADDRESS << 1, TEMP_OUT_H, 1, TempData, 2, 100);
  return (double)(TempData[0] << 8 | TempData[1]) / 340.0 + 36.53;
}


MPU6050Interface MPU6050 = {
  .Initialize = _Initialize, 
  .PollGyro = ReadGyro,
  .PollAccel = ReadAccel,
  .PollThermo = ReadTemp
};
