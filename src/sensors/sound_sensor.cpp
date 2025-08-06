#include "pico/stdlib.h"
#include "pico/time.h"
#include <stdio.h>
#include <stdbool.h>
#include "hardware/gpio.h"
#include "hardware_params.h"

#include "IO/logger/logger.h"
#include "drivers/microphone/microphone.h"
#include "sensors/sound_sensor.h"
#include <cstdio>


// Initialize the sound sensor
void sound_sensor_init() {
    mic_driver::init(4800);
}

// Function to monitor audio levels and check if they exceed a given threshold
bool monitor_audio_level(float threshold) {
    // Read samples and RMS from microphone driver
    std::vector<uint16_t> samples = mic_driver::read(DETECTION_WINDOW_SIZE);
    if (samples.empty()) {
        return false; // No samples read
    }
    float rms_level = mic_driver::calculate_rms(samples);
    return (rms_level > threshold);
}

// Task to monitor sound levels and log if they exceed the threshold
void sound_sensor_task() {
    std::vector<uint16_t> samples = mic_driver::read(DETECTION_WINDOW_SIZE);
    if (samples.empty()) {
        return; // No samples read
    }
    
    float rms_level = mic_driver::calculate_rms(samples);
    if (rms_level > RMS_THRESHOLD) {
        // Triggering an alert
        Logger::SoundLevelAlert alert = Logger::SoundLevelAlert(); 
        Logger::log(alert);
        printf("Sound detected! RMS Level: %.2f\n", rms_level);

    } 
}
