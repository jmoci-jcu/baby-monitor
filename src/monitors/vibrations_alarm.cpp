


#include <cstdint> // For int16_t
#include <cstdlib> // For std::abs
#include <cstdio>  // For printf

#include "pico/stdlib.h" // For stdio functions.   example: printf
#include "drivers/accelerometer/accelerometer.h"

// Internal state – only visible inside this file
static bool mover = false;
static absolute_time_t last_change_time = {0}; // Ensure proper initialization
static int16_t last_buffer[3] = {0}; // Ensure proper initialization


void vibrations_alarm() {


    // Check if any axis changed significantly
    bool significant = false;
    int16_t g_buffer[3];
    read_axis(g_buffer);  // Reads latest accelerometer data
    // Check if any axis changed significantly
    for (int i = 0; i < 3; i++) {
        if (std::abs(g_buffer[i] - last_buffer[i]) > 1000) {
            significant = true;
            break;
        }
    }

    if (significant) {
        mover = true;
        last_change_time = get_absolute_time();

        // Update the buffer after detecting movement
        for (int i = 0; i < 3; i++) {
            last_buffer[i] = g_buffer[i];
        }
    }

    // Invalidate if no significant change for 20 seconds
    if (absolute_time_diff_us(last_change_time, get_absolute_time()) > 1 * 1000000) {
        mover = false;
    }

    // Report movement only when mover is true
    if (mover) {
        printf("Movement detected!\n");
        printf("Raw Accel - X: %d, Y: %d, Z: %d\n", g_buffer[0], g_buffer[1], g_buffer[2]);
    }
}





