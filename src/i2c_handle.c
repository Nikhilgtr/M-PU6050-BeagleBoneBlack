#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <i2c_handle.h>

/*
 *This function open the I2C device wrt the address given
 *IN @
 * i2c_line for ex. /dev/i2c_2
 * fd = File descripter
 * address = address of the i2c device
 *
 *OUT @
 * i2c_err_t = error code for i2c device
 */
 

i2c_err_t i2c_open_device(int i2c_line, int *fd, int add){

    char buff[20];
    int rc;

    sprintf(buff, "/dev/i2c-%d", i2c_line);
    *fd = open(buff, O_RDWR);
    if(fd != NULL) 
        printf("Device Opened\n");
    else {
        printf("Error!! Device Unavailable\n");
        return I2C_FAIL;
    }
    rc = ioctl(*fd, I2C_SLAVE, add);
    if(rc == -1) {
        printf("IOCTL Error!!\n");
         return I2C_FAIL;
    }
    return I2C_SUCCESS;
}

/*
 *This function send data to i2c device after opening the device
 *with address passed in the open i2c function
 */

i2c_err_t i2c_get_reg(int fd, uint8_t *buff, int len)
{
    int rc;
    rc = read(fd, buff, len);
    if(rc == -1) {
        printf("Read Failed!!\n");
        return I2C_FAIL;   
    }
    return I2C_SUCCESS;
}

/*
 *This function receive data from i2c device after opening the device
 *with address passed in the open i2c function
 */

i2c_err_t i2c_set_reg(int fd, uint8_t *buff, int len)
{
    int rc;
    rc = write(fd, buff, len);
    if(rc == -1) {
        printf("write Failed!!\n");
        return I2C_FAIL;   
    }
    return I2C_SUCCESS;
}

