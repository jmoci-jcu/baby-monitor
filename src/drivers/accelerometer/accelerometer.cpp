#include "hardware/i2c.h"
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include <stdio.h>

#include "hardware_params.h"
#include "accelerometer.h"

namespace accel_driver {
void init(){
    i2c_init(i2c_default,400e3);
    gpio_set_function(I2C_SDA_GPIO,GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL_GPIO,GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA_GPIO);
    gpio_pull_up(I2C_SCL_GPIO);

    // //set rate
    uint8_t data_rate = 0b0110;
    uint8_t bits = 0b0111 | data_rate<<4;
    write_to_reg(ACCEL_CTRL_1,bits);
}
void write_to_reg(uint8_t register_address, uint8_t bits){
    uint8_t writeBuf[2] = {register_address,bits};
    uint8_t ret;
    ret = i2c_write_blocking(ACCEL_I2C,ACCEL_SDA,writeBuf,2,false);
    if(ret==PICO_ERROR_GENERIC){
        printf("accellerometer.cpp - write_to_reg() writing to I2C failed");
        return;
    }
}
uint8_t read_from_reg(uint8_t register_address){
    uint8_t reading;
    uint8_t ret;
    ret = i2c_write_blocking(ACCEL_I2C,ACCEL_SDA,&register_address,1,true);
    if(ret==PICO_ERROR_GENERIC){
        printf("accellerometer.cpp - read_from_reg() writing to I2C failed");
        return 0;
    }
    ret = i2c_read_blocking(ACCEL_I2C,ACCEL_SDA,&reading,1,false);
    if(ret==PICO_ERROR_GENERIC){
        printf("accellerometer.cpp - read_from_reg() reading from I2C failed");
        return 0;
    }
    return reading;
}
//Reads data from the accelerometer to measurements[3] as x,y,z. Only works for 10 bit precision mode.
void get_accelerometer_measurements(int16_t *measurements){
    uint8_t xyz[6] = {0,0,0,0,0,0};
    uint8_t register_address = ACCEL_OUT_X_L | 0b10000000;
    uint8_t ret;
    ret = i2c_write_blocking(ACCEL_I2C,ACCEL_SDA,&register_address,1,true);
    if(ret==PICO_ERROR_GENERIC){
        printf("accellerometer.cpp - get_accelerometer_measurements() writing to I2C failed");
        return;
    }
    ret = i2c_read_blocking(ACCEL_I2C,ACCEL_SDA,xyz,6,false);
    if(ret==PICO_ERROR_GENERIC){
        printf("accellerometer.cpp - get_accelerometer_measurements() reading from I2C failed");
        return;
    }

    for(int i = 0; i < 3; i++){
        uint8_t low = xyz[2*i];
        uint8_t high = xyz[2*i+1];
        uint16_t full = (int16_t)(low | high<<8)>>6;
        measurements[i] = full;
    }
}
//Converts raw accelerometer data to g's. Only works if FS = 00 - precision mode default
void raw_to_gs(int16_t *measurements, float *gs){
    for(int i = 0; i < 3; i++){
        gs[i] = measurements[i]/250.0;
    }
}
}