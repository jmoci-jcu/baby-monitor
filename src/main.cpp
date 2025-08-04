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

#include "IO/logger/logger.h"
#include "drivers/flash/flash.h"
#include "IO/uart_terminal/uart_terminal.h"

#include "sensors/motion.h"
#include "sensors/hdc2010_sensor.h"
#include "sensors/sound_sensor.h"

#include "drivers/accelerometer/accelerometer.h"

#include "monitors/vibrations_alarm.h"   // Vibrations alarm header file
#include "drivers/bluetooth/bluetooth.h"

using namespace flashDriver;


int main(){

   //leave this little block here (put all initialization here)
   stdio_init_all();
   bluetoothDriver::init();
   init_motion_sensor();
   setup_accelerometer();
   //UartTerminal::init();
   mic_driver::init(4800);
   hdc2010_sensor_init();
   Logger::init();
  
   setLogLevel(INFORMATION);

   
   //hang (so interrupts can fire after main has run)
   while(true){
      vibrations_alarm();
      sound_sensor_task();
      hdc2010_sensor_task();
   }
    return 0;  // never reached
}
