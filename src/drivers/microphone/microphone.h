#include <vector>
#include "hardware/gpio.h"
#include "pico/stdlib.h"

extern const uint16_t DETECTION_WINDOW_SIZE;
extern const float RMS_THRESHOLD;
extern const uint16_t DC_BIAS;

namespace mic_driver {
    void init(uint16_t clkdiv ); //48MHz/f_target - 1 to the nearest integer
    bool monitor_audio_level(float threshold); 
    std::vector<uint16_t> read(uint16_t nSamples);

    
}