#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include <array>
#include "WS2812.pio.h" // This header file gets produced during compilation from the WS2812.pio file
#include "drivers/logging/logging.h"

#include "hardware_params.h"

#include "example_scripts/led_example.h"
#include "example_scripts/accelerometer_example.h"
#include "example_scripts/fft_example.h"

#include "drivers/accelerometer/accelerometer.h"
#include "drivers/microphone/microphone.h"
#include "drivers/led/led.h"


int main(){
   //Init
   stdio_init_all();
   led_driver::init();
   accel_driver::init();
   mic_driver::init(1087);
   gpio_init(SWITCH_GPIO);
   gpio_set_dir(SWITCH_GPIO,false);

   //Run each example until switch is pressed
   //delay after switch press to avoid multi press
   while(true){
      while(!gpio_get(SWITCH_GPIO)){
         ledexample::run();
      }
      led_driver::resetAll();
      sleep_ms(500);
      while(!gpio_get(SWITCH_GPIO)){
         accelerometerexample::run();
      }
      led_driver::resetAll();
      sleep_ms(500);
      while(!gpio_get(SWITCH_GPIO)){
         fftexample::run();
      }
      led_driver::resetAll();
      sleep_ms(500);
   }
   
}
