#include <stdio.h>
#include <string.h>
#include <mpu6050.h>

#define I2C_BUS 2

int main(void)
{
    mpu_init();
    mpu_enable(I2C_BUS);
    mpu_get_data();
    mpu_val_print();
    return 0;
}
