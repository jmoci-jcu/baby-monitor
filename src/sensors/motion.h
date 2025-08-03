#ifndef MOTION_H
#define MOTION_H

#include "pico/stdlib.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize the PIR motion sensor on GPIO19.
 *
 * Configures the pin as input with pull-up and registers an IRQ
 * callback on the falling edge to log motion alerts.
 */
void init_motion_sensor(void);

#ifdef __cplusplus
}
#endif

#endif // MOTION_H