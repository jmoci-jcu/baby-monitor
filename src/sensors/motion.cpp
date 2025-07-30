// Detects falling-edge motion events from a PIR sensor on GPIO19

#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware_params.h"
#include "IO/logger/logger.h"
#include "sensors/motion.h"

// PIR output connected to GPIO19
static constexpr uint MOTION_GPIO = 19;

// GPIO IRQ callback: logs a MotionAlert on falling edge
static void motion_gpio_callback(uint gpio, uint32_t events) {
    if (gpio == MOTION_GPIO && (events & GPIO_IRQ_EDGE_FALL)) {
        // Debug print to confirm the ISR is hit
        printf(">>> PIR callback fired! gpio=%u events=0x%08x\n", gpio, events);

        // Now your existing alert
        logger::MotionAlert alert;
        logger::log(alert);
    }
}

// Initialize the PIR motion detector
void init_motion_sensor() {
    // 1) Configure the pin as an input
    gpio_init(MOTION_GPIO);
    gpio_set_dir(MOTION_GPIO, GPIO_IN);

    // 2) Enable the internal pull-up (so it idles HIGH)
    gpio_pull_up(MOTION_GPIO);

    // 3) Arm FALLING edge interrupts
    gpio_set_irq_enabled_with_callback(
        MOTION_GPIO,
        GPIO_IRQ_EDGE_FALL,
        true,
        motion_gpio_callback
    );

    // 4) Debug print
    printf("Motion sensor initialized on GPIO %d\n", MOTION_GPIO);
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
