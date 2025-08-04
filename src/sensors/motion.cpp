// Detects falling-edge motion events from a PIR sensor on GPIO19

#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware_params.h"
#include "IO/logger/logger.h"
#include "sensors/motion.h"

// PIR output connected to GPIO19
#define MOTION_GPIO 19

// GPIO IRQ callback: logs a MotionAlert on rising edge
static void motion_gpio_callback(uint gpio, uint32_t events) {
    if (events & GPIO_IRQ_EDGE_RISE) {
        // confirm we hit the ISR
        printf(">>> PIR rising‑edge! gpio=%u events=0x%08x\n", gpio, events);
        // log your motion alert
        Logger::MotionAlert alert;
        Logger::log(alert);
    }
}


// Initialize the PIR motion detector
void init_motion_sensor()
{
    // 1) Configure the pin as an input
    gpio_init(MOTION_GPIO);
    gpio_set_dir(MOTION_GPIO, GPIO_IN);

    // 2) Optionally, enable pull-down if the PIR idles low
    gpio_pull_down(MOTION_GPIO);

    // 3) Arm RISING edge interrupts (0V → 3.3V transition)
    gpio_set_irq_enabled_with_callback(
        MOTION_GPIO,
        GPIO_IRQ_EDGE_RISE,
        true,
        motion_gpio_callback);

    // 4) Debug print
    printf("Motion sensor initialized on GPIO %d (rising-edge)\n", MOTION_GPIO);
}


/*
Usage (e.g., in main.cpp):

#include "motion.cpp"

int main() {
    stdio_init_all();
    init_motion_sensor();
    while (true) {
        tight_loop_contents();
    }
}
*/
