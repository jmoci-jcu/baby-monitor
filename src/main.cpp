#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include <array>
#include "WS2812.pio.h" // This header file gets produced during compilation from the WS2812.pio file
#include "drivers/logging/logging.h"

#include "hardware_params.h"

#include "example_scripts/led_example.h"
#include "example_scripts/accelerometer_example.h"

#include "IO/logger/logger.h"

#include "sensors/motion.h"


using namespace logger;

int main() {

    stdio_init_all();
    sleep_ms(2000);

    // Initialize PIR motion sensor on GPIO19
    init_motion_sensor();

    // Log an initial humidity level (e.g., 10%)
    HumidityLevel humidityLevel(10);
    log(humidityLevel);

    // Main loop: idle, waiting for interrupts
    while (true) {
        tight_loop_contents();
    }

    return 0;  // never reached
}
