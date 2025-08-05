#include "hardware/i2c.h"
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include <stdio.h>

#include "hardware_params.h"
#include "accelerometer.h"

//registers
#define ACCEL_CTRL_REG_1 0x20
#define ACCEL_FIFO_SRC 0x2F
#define ACCEL_FIFO_CTRL 0x2E
#define ACCEL_CTRL_1 0x20

//xyz register addresses for accelerometer
#define ACCEL_OUT_X_L 0x28
#define ACCEL_OUT_X_H 0x29
#define ACCEL_OUT_Y_L 0x2A
#define ACCEL_OUT_Y_H 0x2B
#define ACCEL_OUT_Z_L 0x2C
#define ACCEL_OUT_Z_H 0x2D


void setup_i2c()   
{
    i2c_init(I2C_INSTANCE, 400 * 1000); //this will get called twice but that is fine
    gpio_set_function(I2C_SDA_GPIO, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL_GPIO, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA_GPIO);
    gpio_pull_up(I2C_SCL_GPIO);
}

bool setup_accelerometer()
{
    setup_i2c();
    write_register(ACCEL_CTRL_REG_1, 0b01100111);
    return true;
}

// Fills an array 'axis' with [x,y,z] values
void read_axis(int16_t *axis)
{
    uint8_t data[6];
    read_registers(ACCEL_OUT_X_L, data, 6); // Read 6 bytes starting from OUT_X_L
    // Combine low and high bytes for each axis
    axis[0] = (int16_t)((data[1] << 8) | data[0]); // X-axis
    axis[1] = (int16_t)((data[3] << 8) | data[2]); // Y-axis
    axis[2] = (int16_t)((data[5] << 8) | data[4]); // Z-axis
}


void read_registers(uint8_t reg, uint8_t *data, int length)
{
    if (length > 1) {
        reg |= 0b10000000; // Set the read bit for multiple registers
    }
    i2c_write_blocking(I2C_INSTANCE, ACCEL_SDA, &reg, 1, true);
    i2c_read_blocking(I2C_INSTANCE, ACCEL_SDA, data, length, false);
}


//WRITE
void write_register(uint8_t reg, uint8_t value)
{
    uint8_t data[2] = {reg, value};
    i2c_write_blocking(I2C_INSTANCE, ACCEL_SDA, data, 2, false);
}
