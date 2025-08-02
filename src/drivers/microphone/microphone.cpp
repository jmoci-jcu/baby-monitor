#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"
#include <vector>

#include "microphone.h"
#include "hardware_params.h"

namespace mic_driver{
    void init(uint16_t clkdiv){
        adc_init();
        adc_gpio_init(MIC_GPIO);
        adc_select_input(MIC_ADC);
        adc_fifo_setup(true,false,0,false,false);
        adc_set_clkdiv(clkdiv);
    }
    std::vector<uint16_t> read(uint16_t nSamples){
        std::vector<uint16_t> reads;
        
        // Reserve space for the number of samples to avoid reallocations
        reads.reserve(nSamples);

        adc_run(true);
        for(int i = 0; i<nSamples; i++){
            reads.push_back(adc_fifo_get_blocking());
        }
        adc_run(false);
        adc_fifo_drain();
        return reads;
    }
}