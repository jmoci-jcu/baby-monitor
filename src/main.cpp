#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include <array>
#include "WS2812.pio.h" // This header file gets produced during compilation from the WS2812.pio file
#include "drivers/logging/logging.h"
#include "lfs.h"

#include "hardware_params.h"

#include "example_scripts/led_example.h"
#include "example_scripts/accelerometer_example.h"

#include "IO/logger/logger.h"
#include "drivers/flash/flash.h"

using namespace logger;
using namespace flashDriver;


int main(){

   stdio_init_all();

   flashDriver::writeNewLog();


   return 0;
}