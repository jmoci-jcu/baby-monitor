#include "pico/stdlib.h"
#include <vector>

namespace accel_driver {
    void init();
    void write_to_reg(uint8_t register_address, uint8_t bits);
    uint8_t read_from_reg(uint8_t register_address);
    void get_accelerometer_measurements(int16_t *measurements);
    void raw_to_gs(int16_t *measurements, float *gs);
}