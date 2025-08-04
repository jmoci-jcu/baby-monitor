


#include <cstdint> // For int16_t
#include <cstdlib> // For std::abs
#include <cstdio>  // For printf

#include "pico/stdlib.h" // For stdio functions.   example: printf
#include "drivers/accelerometer/accelerometer.h"

// Internal state – only visible inside this file
static absolute_time_t last_change_time = {0}; // Ensure proper initialization
static int16_t last_buffer[3] = {0}; // Ensure proper initialization


void vibrations_alarm() {
    // Check if any axis changed significantly
    //testing
    uint16_t delta = 0;
    bool significant = false;
    int16_t g_buffer[3];
    read_axis(g_buffer);  // Reads latest accelerometer data
    // Check if any axis changed significantly
    for (int i = 0; i < 3; i++) {
        if (std::abs(g_buffer[i] - last_buffer[i]) > 1000) {
            delta = std::abs(g_buffer[i] - last_buffer[i]);
            significant = true;
            break;
        }
    }

    if (significant) {
        // Update the buffer after detecting movement
        for (int i = 0; i < 3; i++) {
            last_buffer[i] = g_buffer[i];
        }
        bool is_on_timeout = !(absolute_time_diff_us(last_change_time, get_absolute_time()) > 1 * 1000000);
        if (!is_on_timeout) {
            last_change_time = get_absolute_time();
            printf("Movement detected! - Delta : %i\n",delta);
        }

    }
}





