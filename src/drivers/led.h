#include <array>
#include "pico/stdlib.h"

namespace led_driver
{
//Initialise the object
void init();
//Update the led colour data for a particular led.
void setLED(uint8_t led_index, std::array<uint8_t,3> colour);
//Push led data to leds and block until complete.
void update();
//Reset all leds to off and call update automatically.
void resetAll();
}