

//#include <vector>
#include <stdio.h>
#include <cstdlib>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
//#include "drivers/.h"
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



// namespace accel_driver {
//     void init();
//     void write_to_reg(uint8_t register_address, uint8_t bits);
//     uint8_t read_from_reg(uint8_t register_address);
//     void get_accelerometer_measurements(int16_t *measurements);
//     void raw_to_gs(int16_t *measurements, float *gs);
// }



//         float g_buffer[3]; // Buffer to hold G-force values
//         read_axis_Gforce(g_buffer);
//         printf("G-Force - X: %i, Y: %i, Z: %i\n", g_buffer[0], g_buffer[1], g_buffer[2]);