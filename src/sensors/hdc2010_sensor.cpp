#include "pico/stdlib.h"
#include "pico/time.h"
#include <stdio.h>
#include <stdbool.h>
#include "hardware/gpio.h"
#include "hardware_params.h"

#include "sensors/hdc2010_sensor.h"
#include "IO/logger/logger.h"
#include "drivers/logging/logging.h"
#include "drivers/HDC2010/hdc2010.h"



static volatile bool g_sample_due = false;
static repeating_timer_t g_timer;

static bool sample_timer_cb(repeating_timer_t *t) {
    (void)t;
    g_sample_due = true;
    return true;
}

void hdc2010_sensor_init(void) {
    HDC2010_init();
    add_repeating_timer_ms(10 * 1000, sample_timer_cb, NULL, &g_timer);
    log(INFORMATION, "HDC2010 sensor started; sampling every ~10 s");
}

void hdc2010_sensor_task(void) {
    if (!g_sample_due) return;
    g_sample_due = false;

    float t_c = 0.0f, rh = 0.0f;
    if (HDC2010_read(&t_c, &rh)) {
        uint8_t temp_int = (uint8_t)(t_c < 0 ? 0 : (t_c > 255 ? 255 : (t_c + 0.5f)));
        uint8_t rh_int   = (uint8_t)(rh   < 0 ? 0 : (rh   > 100 ? 100 : (rh   + 0.5f)));

        Logger::TemperatureLevel tlog(temp_int);
        Logger::HumidityLevel hlog(rh_int);

        Logger::log(tlog);
        Logger::log(hlog);
    } else {
        Logger::MotionAlert err;
        err.classifier = "HDC2010 read failed";
        Logger::log(err);
    }
}
