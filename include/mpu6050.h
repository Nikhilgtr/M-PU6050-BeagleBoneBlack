#ifndef MPU6050_H
#define MPU6050_H

#include <stdint.h>

typedef enum mpu_error {
    MPU_SUCCESS = 0,
    MPU_FAIL 
} mpu_err_t;

enum type_of_val { L = 0,H };
enum axis_index {X = 0, Y, Z, TEMP };


#define MPU6050_ADDR 0x68

#define MPU6050_PWR_MGMT_1 0x6B
#define MPU6050_PWR_ENABLE 0
#define MPU6050_ACCEL_XOUT_H 0x3B
#define MPU6050_ACCEL_XOUT_L 0x3C
#define MPU6050_ACCEL_YOUT_H 0x3D
#define MPU6050_ACCEL_YOUT_L 0x3E
#define MPU6050_ACCEL_ZOUT_H 0x3F
#define MPU6050_ACCEL_ZOUT_L 0x40
#define MPU6050_TEMP_OUT_H 0x41
#define MPU6050_TEMP_OUT_L 0x42

mpu_err_t mpu_enable(int i2c_line);
mpu_err_t mpu_get_data(void);
void mpu_val_print(void);


#endif //MPU6050_H
