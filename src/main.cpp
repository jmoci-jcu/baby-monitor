#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include <array>
#include "WS2812.pio.h" // This header file gets produced during compilation from the WS2812.pio file
#include "drivers/logging/logging.h"
#include "drivers/microphone/microphone.h"

#include "hardware_params.h"

#include "example_scripts/led_example.h"
#include "example_scripts/accelerometer_example.h"

#include "IO/logger/logger.h"

using namespace logger;
// threshold = 100.0f

int main(){
    stdio_init_all();
    
    // Initialize microphone
    mic_driver::init(4800);
    
    printf("Microphone detection started...\n");
    
    // Main loop
    while (true) {
         if (mic_driver::monitor_audio_level(100.0f)) { 
            printf("Baby activity detected!\n");
         }
        sleep_ms(10);
    }
    
    return 0;
}




