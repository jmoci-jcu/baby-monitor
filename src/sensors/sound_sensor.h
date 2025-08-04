#pragma once

void sound_sensor_init();

bool monitor_audio_level(float threshold);

void sound_sensor_task();
