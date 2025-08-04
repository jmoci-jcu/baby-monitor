#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include <array>
#include "WS2812.pio.h" // This header file gets produced during compilation from the WS2812.pio file
#include "drivers/logging/logging.h"
#include "drivers/microphone/microphone.h"
#include "lfs.h"

#include "hardware_params.h"

#include "example_scripts/led_example.h"
#include "example_scripts/accelerometer_example.h"

#include "IO/logger/logger.h"
#include "drivers/flash/flash.h"
#include "IO/uart_terminal/uart_terminal.h"

#include "sensors/motion.h"
#include "sensors/hdc2010_sensor.h"

using namespace logger;
using namespace flashDriver;


int main(){

   //leave this little block here (put all initialization here)
   stdio_init_all();
   sleep_ms(2000);
   init_motion_sensor();
   UartTerminal::init();
   mic_driver::init(4800);
   hdc2010_sensor_init();
   init_motion_sensor();
  
   setLogLevel(INFORMATION);

   //test code for logging
   for(int i = 0; i < 10; i++){
      HumidityLevel hlevel = HumidityLevel(i);
      log(hlevel);
   }
   
   //hang (so interrupts can fire after main has run)
   while(true){
    if (mic_driver::monitor_audio_level(100.0f)) { 
            printf("Baby activity detected!\n");
         }
     hdc2010_sensor_task();
   }
    return 0;  // never reached
}
