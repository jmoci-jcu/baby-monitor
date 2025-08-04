


#include <cstdint> // For int16_t
#include <cstdlib> // For std::abs
#include <cstdio>  // For printf

#include "pico/stdlib.h" // For stdio functions.   example: printf
#include "drivers/accelerometer/accelerometer.h"
#include "IO/logger/logger.h"

// Internal state – only visible inside this file
static absolute_time_t last_change_time = {0}; // Ensure proper initialization
static int16_t last_buffer[3] = {0}; // Ensure proper initialization


void vibrations_alarm() {
    // Check if any axis changed significantly
    bool significant = false;
    int16_t g_buffer[3];
    read_axis(g_buffer);  // Reads latest accelerometer data
    // Check if any axis changed significantly
    for (int i = 0; i < 3; i++) {
        uint16_t delta = std::abs(g_buffer[i] - last_buffer[i]);
        if (delta > 1000) {
            significant = true;
        }
    }

    if(!significant){return;}

    // Update the buffer after detecting movement
    for (int i = 0; i < 3; i++) {
        last_buffer[i] = g_buffer[i];
    }
    bool is_on_timeout = !(absolute_time_diff_us(last_change_time, get_absolute_time()) > 1 * 1000000);
    if (!is_on_timeout) {
        last_change_time = get_absolute_time();
        Logger::VibrationLevelAlert vibrationLog = Logger::VibrationLevelAlert();
        Logger::log(vibrationLog);
    }
}





