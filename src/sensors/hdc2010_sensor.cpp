#include "pico/stdlib.h"
#include "pico/time.h"
#include <stdio.h>
#include <stdbool.h>
#include "hardware/gpio.h"
#include "hardware_params.h"  // I2C pins, instance, etc.
#include "sensors/hdc2010_sensor.h"  // hdc2010_sensor_init, hdc2010_sensor_task

#include "drivers/logging/logging.h"   // your logger (log(), setLogLevel(), LogLevel)
#include "drivers/HDC2010/hdc2010.h"   

static volatile bool g_sample_due = false;
static repeating_timer_t g_timer;

// IRQ context: don't do I2C or printf here — just set a flag.
static bool sample_timer_cb(repeating_timer_t *t) {
    (void)t;
    g_sample_due = true;
    return true; // keep repeating
}

void hdc2010_sensor_init(void) {
    // Init the sensor/I2C
    HDC2010_init();

    // Start a repeating timer every ~10 seconds
    // (positive interval => first tick ~10 s from now)
    add_repeating_timer_ms(10 * 1000, sample_timer_cb, NULL, &g_timer);

    log(INFORMATION, "HDC2010 sensor started; sampling every ~10 s");
}

void hdc2010_sensor_task(void) {
    if (!g_sample_due) return;
    g_sample_due = false;

    float t_c = 0.0f, rh = 0.0f;
    if (HDC2010_read(&t_c, &rh)) {
        char buf[96];
        // Format once, then pass to your logger
        // (requires printf float support; see CMake note below)
        snprintf(buf, sizeof(buf),
                 "HDC2010 reading: Temp=%.2f C, Humidity=%.2f %%RH",
                 t_c, rh);
        log(INFORMATION, buf);
    } else {
        log(WARNING, "HDC2010 read failed");
    }
}
