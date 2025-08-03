#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include <array>
#include "WS2812.pio.h" // This header file gets produced during compilation from the WS2812.pio file
#include "drivers/logging/logging.h"

#include "hardware_params.h"

#include "example_scripts/led_example.h"

#include "IO/logger/logger.h"

#include "drivers/accelerometer/accelerometer.h"

#include "monitors/vibrations_alarm.h"   // Vibrations alarm header file


// using namespace logger;
      

// bool mover = false; // Flag to indicate if a significant movement has been detected
// extern void vibrations_alarm_init(); // Function to initialize the vibrations alarm

// int main(){

//    stdio_init_all();
//    setup_accelerometer();

//    while (true) {
//       int16_t g_buffer[3]; // Buffer to hold raw 16-bit axis data
//       read_axis(g_buffer); // Replace with your function that reads int16_t values

//       vibrations_alarm_init(); // Initialize the vibrations alarm
      
//       if(mover) {
//          printf("Movement detected!\n");
         
//          printf("Raw Accel - X: %d, Y: %d, Z: %d\n", g_buffer[0], g_buffer[1], g_buffer[2]);
//          //mover = false; // Reset the mover flag after handling
//       }
      
//       sleep_ms(100);
//    }

//    return 0;
// }


// bool mover = false; // Global flag — defined once

// extern void check_for_vibrations(int16_t* data); // Called every loop

// int main() {
//     stdio_init_all();
//     setup_accelerometer();

//     while (true) {
//         int16_t g_buffer[3]; // Holds X, Y, Z axis raw data
//         read_axis(g_buffer); // Fill the buffer with current data

//         check_for_vibrations(g_buffer); // Updates mover flag internally

//         if (mover) {
//             printf("Movement detected!\n");
//             printf("Raw Accel - X: %d, Y: %d, Z: %d\n", g_buffer[0], g_buffer[1], g_buffer[2]);

//             // Optionally reset the flag:
//             // mover = false;
//         }

//         sleep_ms(100);
//     }

//     return 0;
// }



int main() {
    stdio_init_all();
    setup_accelerometer();

    while (true) {
        vibrations_alarm();  // Hands off to internal logic
        sleep_ms(100);
    }

    return 0;
}