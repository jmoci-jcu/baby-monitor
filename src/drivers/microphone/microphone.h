#include <vector>
#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <cstdint>

extern const uint16_t DETECTION_WINDOW_SIZE;
extern const float RMS_THRESHOLD;
extern const uint16_t DC_BIAS;

namespace mic_driver {
    // Initialize the microphone with clock divider
    void init(uint16_t clkdiv);
    
    // Function to read a number of samples from the ADC
    std::vector<uint16_t> read(uint16_t nSamples);
    
    // Calculate RMS of audio samples
    float calculate_rms(const std::vector<uint16_t>& samples);
    
    // Monitor audio level and log if it exceeds the threshold
    bool monitor_audio_level(float threshold);
}