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
        logger::MotionAlert alert;
        logger::log(alert);
    }
}

// Initialize the PIR motion detector
void init_motion_sensor() {
    // Configure pin as input with pull-up
    gpio_init(MOTION_GPIO);
    gpio_set_dir(MOTION_GPIO, GPIO_IN);
    gpio_pull_up(MOTION_GPIO);

    // Enable falling-edge IRQ with our callback
    gpio_set_irq_enabled_with_callback(
        MOTION_GPIO,
        GPIO_IRQ_EDGE_FALL,
        true,
        motion_gpio_callback
    );
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
