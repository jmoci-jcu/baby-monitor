#include "hardware/pio.h"
#include "pico/stdlib.h"
#include "WS2812.pio.h"
#include <array>

#include "led.h"
#include "hardware_params.h"

uint32_t led_data[LED_COUNT];

void led_driver::update(){
    // block until any pending buffers are sent out
    // TODO implement mode to clear the buffer instead
    while(!pio_sm_is_tx_fifo_empty(LED_PIO,0)){
        sleep_us(1);
    }
    // wait until led is ready to accept instructions (reset delay)
    sleep_us(300);
    for(uint8_t i = 0; i < LED_COUNT; i++){
        pio_sm_put_blocking(LED_PIO, 0, led_data[i]);
    }
}

void led_driver::resetAll(){
    for(uint8_t i; i < LED_COUNT; i++){
        std::array<uint8_t,3> colour = {0, 0, 0};
        setLED(i,colour);
    }
    update();
}

void led_driver::init(){
    uint pio_program_offset = pio_add_program(LED_PIO, &ws2812_program);
    ws2812_program_init(LED_PIO, 0, pio_program_offset, LED_GPIO, 800000, false);
}

void led_driver::setLED(uint8_t led_index, std::array<uint8_t,3> colour){
    uint8_t red = colour[0];
    uint8_t green = colour[1];
    uint8_t blue = colour[2];
    //TODO check led index (error?, fail silent?)
    led_data[led_index] = (red << 24) | (green << 16) | (blue << 8);    
}

