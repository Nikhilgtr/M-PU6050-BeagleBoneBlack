#include <stdio.h>
#include <getopt.h>
#include <mpu6050.h>
#include <stdlib.h>
#include <unistd.h>

#define I2C_BUS_FOR_MPU6050 2

void mpu_ret(void);
void print_usage(void);
void mpu_ret_sec(int sec);

int main(int argc, char **argv)
{
    int option, sflag = 0;

    mpu_enable(I2C_BUS_FOR_MPU6050);

    if(argc < 2) {
        mpu_ret();
        exit(2);
    }

    while((option = getopt(argc,argv,"s:") != -1)) {
         switch(option) {

            case 's':
                if(sflag)
                    print_usage();
                else
                    sflag++;
                mpu_ret_sec(atoi(optarg));
                break;

            default:
                print_usage();
        }
    }

    return 0;
}

void mpu_ret(void)
{

    mpu_get_data();
    mpu_val_print();
}

void mpu_ret_sec(int sec)
{
    while(sec--) {
        mpu_ret();
        sleep(1);
    }
}

void print_usage(void)
{
    printf("\nUsage: \nFor one reading use without arguements\n\n");
    printf("         For reapeated readings enter seconds as -s as argument\n");
    printf("         For ex. \"./mpu6050 -s 2\"\n");
    exit(1);
}
