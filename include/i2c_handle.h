#ifndef I2C_HANDLE_H
#define I2C_HANDLE_H
#include <stdint.h>

typedef enum i2c_error{
    I2C_SUCCESS = 0,
    I2C_FAIL
}i2c_err_t;

i2c_err_t i2c_set_reg(int fd, uint8_t *buff, int len);
i2c_err_t i2c_get_reg(int fd, uint8_t *buff, int len);
i2c_err_t i2c_open_device(int i2c_line, int *fd, int add);
#endif //I2C_HANDLE
