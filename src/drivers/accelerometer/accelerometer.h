

#include <stdio.h>
#include <cstdlib>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/i2c.h"
#include "hardware_params.h"

//Debug libraries
#include "pico/binary_info.h"
#include "drivers/logging/logging.h"

void setup_i2c();            // Initializes the I2C interface for communication with the accelerometer.
bool setup_accelerometer();

// Reads a single byte from the WHO_AM_I register to verify the accelerometer is connected and functioning.
void read_accelerometer(int16_t &x, int16_t &y, int16_t &z);

// Reads and writes registers on the accelerometer.
uint8_t read_register(uint8_t reg);
void write_register(uint8_t reg, uint8_t value);

void read_axis(int16_t *buffer);

void read_registers(uint8_t reg, uint8_t * data, int length);

void read_axis_Gforce(float *buffer); 

