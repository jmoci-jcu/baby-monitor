#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/pio.h"
#include <array>
#include "WS2812.pio.h" // This header file gets produced during compilation from the WS2812.pio file
#include "drivers/logging/logging.h"

#include "hardware_params.h"
#include "accelerometer_example.h"
#include "drivers/accelerometer/accelerometer.h"
#include "drivers/led/led.h"

void accelerometerexample::run()
{
    int16_t xyz[3];
    float xyzg[3];
    accel_driver::get_accelerometer_measurements(xyz);
    accel_driver::raw_to_gs(xyz,xyzg);
    printf("X : %f, ",xyzg[0]);
    printf("Y : %f, ",xyzg[1]);
    printf("Z : %f\n",xyzg[2]); 

    //set colour of led based on accelerometer reading
    uint8_t brightness = 0;
    uint8_t leds[3][4] = {{4,5,6,7},{8,9,10,11},{0,1,2,3}};
    uint8_t axis_channel[3] = {0,1,2};
    std::array<uint8_t,3> zero = {0,0,0};
    for(int iRow = 0; iRow < 3; iRow++){
        std::array<uint8_t,3> colour = {0,0,0};
        if(xyz[iRow] > -25 && xyz[iRow] < 25){
            brightness = -1*xyz[iRow];
            colour[axis_channel[iRow]] = brightness;
            led_driver::setLED(leds[iRow][0],zero);
            led_driver::setLED(leds[iRow][1],colour);
            led_driver::setLED(leds[iRow][2],colour);
            led_driver::setLED(leds[iRow][3],zero);
        }else if(xyz[iRow] < 0){
            brightness = -1*xyz[iRow];
            colour[axis_channel[iRow]] = brightness;
            led_driver::setLED(leds[iRow][0],colour);
            led_driver::setLED(leds[iRow][1],zero);
            led_driver::setLED(leds[iRow][2],zero);
            led_driver::setLED(leds[iRow][3],zero);
        }else{
            brightness = xyz[iRow];
            colour[axis_channel[iRow]] = brightness;
            led_driver::setLED(leds[iRow][0],zero);
            led_driver::setLED(leds[iRow][1],zero);
            led_driver::setLED(leds[iRow][2],zero);
            led_driver::setLED(leds[iRow][3],colour);
        }
    }
    led_driver::update();
    
    sleep_ms(100);
}    
