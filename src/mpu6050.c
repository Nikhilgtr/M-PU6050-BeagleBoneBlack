#include <stdio.h>
#include <i2c_handle.h>
#include <mpu6050.h>
#include <string.h>
#include <stdlib.h>

mpu_err_t mpu_reg_data(uint8_t reg);

int fd;
uint16_t data_reg[4] = {0};       //[0]->x, [1]->y, [2]->z, [3]->t


uint8_t reg_addr[] = {
    MPU6050_ACCEL_XOUT_H,
    MPU6050_ACCEL_XOUT_L,
    MPU6050_ACCEL_YOUT_H,
    MPU6050_ACCEL_YOUT_L,
    MPU6050_ACCEL_ZOUT_H,
    MPU6050_ACCEL_ZOUT_L,
    MPU6050_TEMP_OUT_H, 
    MPU6050_TEMP_OUT_L
};

#define REG_ADDR_LEN (sizeof(reg_addr)/sizeof(*reg_addr))


void mpu_init(void)
{
}

mpu_err_t mpu_enable(int i2c_line)
{
    int rc;
    uint8_t buff[2];

    rc = i2c_open_device(i2c_line, &fd, MPU6050_ADDR);    
    if(rc == I2C_FAIL) {
        printf("Opening device Failed!!\n");
        return MPU_FAIL;
    }
    buff[0] = MPU6050_PWR_MGMT_1;
    buff[1] = MPU6050_PWR_ENABLE;

    rc = i2c_set_reg(fd, buff, 2);
    if(rc == I2C_FAIL)
        return MPU_FAIL;
    return MPU_SUCCESS;
}

uint8_t register_get(uint8_t reg)
{
    int rc;
    rc = i2c_set_reg(fd, &reg, 1);
    rc = i2c_get_reg(fd, &reg, 1);
    return reg;
}

static inline int convert_val(uint8_t *buff)
{
    return ((buff[0] << 8) + buff[1]);
}

void combine_reg_data(uint8_t *buff)
{
    static int count_of_axis;
    switch(count_of_axis)
    {
        case X:
            data_reg[X] = convert_val(buff);
            break;

        case Y:
            data_reg[Y] = convert_val(buff);
            break;

        case Z:
            data_reg[Z] = convert_val(buff);
            break;

        case TEMP:
            data_reg[TEMP] = convert_val(buff);
            break;
    }
    if(count_of_axis == TEMP) {
        count_of_axis = 0;
        return;
    }
    else
        count_of_axis++;
}

mpu_err_t mpu_get_data(void)
{   
    uint8_t buff[2];
    int i, j;

    for(i = 0, j = 0;i < REG_ADDR_LEN; i++, j++)
    {
        buff[j] = register_get(reg_addr[i]);
        if(j == 1)
        {
            j = 0;
            combine_reg_data(buff);
        }
    }
}



void mpu_val_print(void)
{
    char buff[500];
    char temp[100];
    float temperature;
    temperature = (((float)data_reg[3] / 10)-32)*5/9;
    system("clear");
    sprintf(buff,"#####################################################\n");   
    strcat(buff,"******************Accelerometer Data*****************\n");
    sprintf(temp,"X = %d\n",data_reg[0]);
    strcat(buff,temp);
    sprintf(temp,"Y = %d\n",data_reg[1]);
    strcat(buff,temp);
    sprintf(temp,"X = %d\n",data_reg[2]);
    strcat(buff,temp);
    strcat(buff,"*******************Temperature Data******************\n");
    sprintf(temp,"Temperature = %.2f\n",temperature);
    strcat(buff,temp);
    strcat(buff,"#####################################################\n\n");   
    printf("%s",buff);

}

