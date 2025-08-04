


// #include <stdio.h>
// #include "pico/stdlib.h"
// #include "hardware/gpio.h"
// #include "hardware/i2c.h"
// #include <cstdio>

// void vibrations_alarm_init(); 

// extern unsigned int g_buffer; // Declaration of g_buffer



#ifndef VIBRATIONS_ALARM_H
#define VIBRATIONS_ALARM_H

#include <stdint.h>

// Main entry point: run this in your loop with accelerometer data
void vibrations_alarm();

#endif