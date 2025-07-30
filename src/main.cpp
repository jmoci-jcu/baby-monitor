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

#define TEST_GPIO 19

using namespace logger;

int main()
{

   stdio_init_all();
   // init_motion_sensor();
   HumidityLevel humidityLevel = HumidityLevel(10);
   log(humidityLevel);
// Configure GPIO19 as input with internal pull‑up (idles HIGH)
    gpio_init(TEST_GPIO);
    gpio_set_dir(TEST_GPIO, GPIO_IN);
    gpio_set_pulls(TEST_GPIO, false, true);

    while (true) {
        bool level = gpio_get(TEST_GPIO);
        // print numeric or human‑readable state
        printf("GPIO19 is %s\n", level ? "HIGH" : "LOW");
        // or: printf("%d\n", level);
        sleep_ms(500);  // sample every 50 ms (20 Hz); lower for faster updates
    }
}