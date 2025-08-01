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
#include "IO/uart_terminal/uart_terminal.h"

#include "sensors/motion.h"


using namespace logger;
using namespace flashDriver;

int main(){

   //leave this little block here (put all initialization here)
   stdio_init_all();
   init_motion_sensor();
   UartTerminal::init();

   //test code for logging
   for(int i = 0; i < 10; i++){
      HumidityLevel hlevel = HumidityLevel(i);
      log(hlevel);
   }
   
   //hang (so interrupts can fire after main has run)
   while(true){
      sleep_ms(1);
   }
    return 0;  // never reached
}
