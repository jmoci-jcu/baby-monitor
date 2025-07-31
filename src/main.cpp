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

using namespace logger;
      
int main(){

   stdio_init_all();
   setup_accelerometer();

   while (true) {
      int16_t g_buffer[3]; // Buffer to hold raw 16-bit axis data
      read_axis(g_buffer); // Replace with your function that reads int16_t values
      printf("Raw Accel - X: %d, Y: %d, Z: %d\n", g_buffer[0], g_buffer[1], g_buffer[2]);
      sleep_ms(100);
   }

   return 0;
}


