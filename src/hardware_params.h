#pragma once
#include "hardware/flash.h"

// I2C

#define I2C_SDA_GPIO 2
#define I2C_SCL_GPIO 3
#define I2C_INSTANCE i2c1

// Accelerometer

#define ACCEL_SDA 0x19

// Microphone

#define MIC_GPIO 26
#define MIC_ADC 0

// Flash

#define FLASH_RESERVED_PROGRAM_BLOCKS 256
#define FLASH_PAGE_WIDTH_BYTES 256
#define FLASH_BLOCK_WIDTH_BYTES 16*FLASH_PAGE_WIDTH_BYTES
#define FLASH_BASE (XIP_BASE + FLASH_RESERVED_PROGRAM_BLOCKS * FLASH_BLOCK_WIDTH_BYTES)
#define FLASH_BLOCK_COUNT 512 // only have access to 2MB of flash, due to value hardcoded to SDK 

// Debug
#define DEBUG_UART uart0
#define DEBUG_IRQ UART0_IRQ

// Bluetooth
#define BT_GPIO_TX 8
#define BT_GPIO_RX 9
#define BT_UART_INSTANCE uart1

// Logger
#define LOGGER_FLUSH_FREQ_MS 1000