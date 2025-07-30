#include "hardware/i2c.h"
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include <stdio.h>

#include "hardware_params.h"
#include "accelerometer.h"


//THIS SECTION GOES IN THE MAIN SECTION, IF YOU WANT TO USE A BUTTON TO SWITCH BETWEEN TASKS
volatile bool end_task = false; // Flag to control the end of a task
    void gpio_callback(uint gpio, uint32_t events) {
        printf("Button pressed! Changing task\n");
        end_task = true; // Set the flag to end the current task
    }


void setup_i2c()   
{
    i2c_init(I2C_INSTANCE, 400 * 1000);
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_PIN);
    gpio_pull_up(SCL_PIN);
}

bool setup_accelerometer()
{
    setup_i2c();
    write_register(ACCEL_CTRL_REG_1, 0b01100111);
    return true;
}

// Reads the accelerometer and fills the axis array with G-force values
void read_axis_Gforce(float *axis)
{
    uint8_t data[6];
    read_registers(ACCEL_OUT_X_L, data, 6); // Read 6 bytes starting from OUT_X_L
    // Combine low and high bytes for each axis
    axis[0] = (int16_t)((data[1] << 8) | data[0]); // X-axis
    axis[1] = (int16_t)((data[3] << 8) | data[2]); // Y-axis
    axis[2] = (int16_t)((data[5] << 8) | data[4]); // Z-axis

    // Convert to G-force values (assuming sensitivity of 16384 LSB/g)
    axis[0] /= 16384.0;
    axis[1] /= 16384.0;
    axis[2] /= 16384.0;
}

void read_registers(uint8_t reg, uint8_t *data, int length)
{
    if (length > 1)
    {
        reg |= 0b10000000; // Set the read bit for multiple registers
    }
    i2c_write_blocking(I2C_INSTANCE, ACCEL_I2C_ADDRESS, &reg, 1, true);
    i2c_read_blocking(I2C_INSTANCE, ACCEL_I2C_ADDRESS, data, length, false);
}

//WRITE
void write_register(uint8_t reg, uint8_t value)
{
    uint8_t data[2] = {reg, value};
    i2c_write_blocking(I2C_INSTANCE, ACCEL_I2C_ADDRESS, data, 2, false);
}


void main_loop(){
    while (true){
        float g_buffer[3]; // Buffer to hold G-force values
            read_axis_Gforce(g_buffer);
            printf("G-Force - X: %i, Y: %i, Z: %i\n", g_buffer[0], g_buffer[1], g_buffer[2]);
            //notice %i might be incorrect, as g_buffer is a float array, so it should be %f
        sleep_ms(100);
        end_task = false;
    }
}





















// namespace accel_driver {
// void init(){
//     i2c_init(i2c_default,400e3);
//     gpio_set_function(I2C_SDA_GPIO,GPIO_FUNC_I2C);
//     gpio_set_function(I2C_SCL_GPIO,GPIO_FUNC_I2C);
//     gpio_pull_up(I2C_SDA_GPIO);
//     gpio_pull_up(I2C_SCL_GPIO);

//     // //set rate
//     uint8_t data_rate = 0b0110;
//     uint8_t bits = 0b0111 | data_rate<<4;
//     write_to_reg(ACCEL_CTRL_1,bits);
// }
// void write_to_reg(uint8_t register_address, uint8_t bits){
//     uint8_t writeBuf[2] = {register_address,bits};
//     uint8_t ret;
//     ret = i2c_write_blocking(ACCEL_I2C,ACCEL_SDA,writeBuf,2,false);
//     if(ret==PICO_ERROR_GENERIC){
//         printf("accellerometer.cpp - write_to_reg() writing to I2C failed");
//         return;
//     }
// }
// uint8_t read_from_reg(uint8_t register_address){
//     uint8_t reading;
//     uint8_t ret;
//     ret = i2c_write_blocking(ACCEL_I2C,ACCEL_SDA,&register_address,1,true);
//     if(ret==PICO_ERROR_GENERIC){
//         printf("accellerometer.cpp - read_from_reg() writing to I2C failed");
//         return 0;
//     }
//     ret = i2c_read_blocking(ACCEL_I2C,ACCEL_SDA,&reading,1,false);
//     if(ret==PICO_ERROR_GENERIC){
//         printf("accellerometer.cpp - read_from_reg() reading from I2C failed");
//         return 0;
//     }
//     return reading;
// }
// //Reads data from the accelerometer to measurements[3] as x,y,z. Only works for 10 bit precision mode.
// void get_accelerometer_measurements(int16_t *measurements){
//     uint8_t xyz[6] = {0,0,0,0,0,0};
//     uint8_t register_address = ACCEL_OUT_X_L | 0b10000000;
//     uint8_t ret;
//     ret = i2c_write_blocking(ACCEL_I2C,ACCEL_SDA,&register_address,1,true);
//     if(ret==PICO_ERROR_GENERIC){
//         printf("accellerometer.cpp - get_accelerometer_measurements() writing to I2C failed");
//         return;
//     }
//     ret = i2c_read_blocking(ACCEL_I2C,ACCEL_SDA,xyz,6,false);
//     if(ret==PICO_ERROR_GENERIC){
//         printf("accellerometer.cpp - get_accelerometer_measurements() reading from I2C failed");
//         return;
//     }

//     for(int i = 0; i < 3; i++){
//         uint8_t low = xyz[2*i];
//         uint8_t high = xyz[2*i+1];
//         uint16_t full = (int16_t)(low | high<<8)>>6;
//         measurements[i] = full;
//     }
// }
// //Converts raw accelerometer data to g's. Only works if FS = 00 - precision mode default
// void raw_to_gs(int16_t *measurements, float *gs){
//     for(int i = 0; i < 3; i++){
//         gs[i] = measurements[i]/250.0;
//     }
// }
// }