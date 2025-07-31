#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"
#include <vector>
#include <numeric>

#include "IO/logger/logger.h"
#include "drivers/microphone/microphone.h"
#include "hardware_params.h"
#include "constants.h"
#include <cmath>

const uint16_t DETECTION_WINDOW_SIZE = 512;
const float RMS_THRESHOLD = 100.0f;
const uint16_t DC_BIAS = 2048;

namespace mic_driver{
    void init(uint16_t clkdiv){
        adc_init();
        adc_gpio_init(MIC_GPIO);
        adc_select_input(MIC_ADC);
        adc_fifo_setup(true,false,0,false,false);
        adc_set_clkdiv(clkdiv);
    }

    // Function to read a number of samples from the ADC
    std::vector<uint16_t> read(uint16_t nSamples){
        std::vector<uint16_t> reads;
        reads.reserve(nSamples);  // Reserve space for efficiency

        adc_run(true);
        for(int i = 0; i<nSamples; i++){
            reads.push_back(adc_fifo_get_blocking());
        }
        adc_run(false);
        adc_fifo_drain();
        return reads;
    }

   // Calculate RMS of audio samples
   float calculate_rms(const std::vector<uint16_t>& samples) {
        if (samples.empty()) return 0.0f;

        float sum_of_squares = 0.0f;
        for (uint16_t sample: samples) {
            float ac_sample = static_cast<float>(sample) - DC_BIAS;
            sum_of_squares += ac_sample * ac_sample;
        }

        return std::sqrt(sum_of_squares / samples.size());
    }

    bool monitor_audio_level(float threshold) {
        auto samples = read(DETECTION_WINDOW_SIZE);
        float rms_level = calculate_rms(samples);
        
        if (rms_level > threshold) {
            // Log the detection event
            logger::SoundLevelAlert alert;
            logger::log(alert);
            return true;
        }
        return false;
    }

}