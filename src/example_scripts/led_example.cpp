#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/pio.h"
#include <array>
#include "WS2812.pio.h" // This header file gets produced during compilation from the WS2812.pio file
#include "drivers/logging/logging.h"

#include "hardware_params.h"
#include "led_example.h"
#include "drivers/led/led.h"

void ledexample::run()
{
// LED test script
std::array<uint8_t, 3> colour;
//One Animation Cycle
for(uint8_t i = 0; i < LED_COUNT; i++){
    colour = {(uint8_t)(10*i), 0, (uint8_t)(200-5*i)};
    led_driver::setLED(i,colour);
    led_driver::update();
    if (gpio_get(SWITCH_GPIO)){
        break;
    }
    sleep_ms(100);
}
led_driver::resetAll();
}
