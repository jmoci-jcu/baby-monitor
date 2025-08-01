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
#include "sensors/hdc2010_sensor.h"


using namespace logger;

int main() {
    stdio_init_all();
    sleep_ms(2000);

    setLogLevel(INFORMATION);

    // PIR motion sensor
    init_motion_sensor();

    // *** Start the ~10 s HDC2010 sampler ***
    hdc2010_sensor_init();

    // Remove the old placeholder humidity log:
    // HumidityLevel humidityLevel(10);
    // log(humidityLevel);

    while (true) {
        // Will log two lines (Temp + Humidity) about every 10 seconds.
        hdc2010_sensor_task();

        tight_loop_contents();
    }

    return 0;  // never reached
}