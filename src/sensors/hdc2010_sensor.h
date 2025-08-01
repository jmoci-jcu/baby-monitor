#pragma once

// Initializes the HDC2010 and starts a ~10 s repeating timer.
// Call this once at startup (after stdio_init_all()).
void hdc2010_sensor_init(void);

// Call this frequently from your main loop.
// When a sample is due, it reads the sensor and logs the values.
void hdc2010_sensor_task(void);
