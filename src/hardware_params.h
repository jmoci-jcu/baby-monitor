//LED
#define LED_PIO pio0
#define LED_GPIO 14
#define LED_COUNT 12
#define I2C_SDA_GPIO 16
#define I2C_SCL_GPIO 17

//Accelerometer
#define ACCEL_I2C &i2c0_inst

//slave addr
#define ACCEL_SDA 0x19

//registers
#define ACCEL_FIFO_SRC 0x2F
#define ACCEL_FIFO_CTRL 0x2E
#define ACCEL_CTRL_1 0x20

//xyz
#define ACCEL_OUT_X_L 0x28
#define ACCEL_OUT_X_H 0x29
#define ACCEL_OUT_Y_L 0x2A
#define ACCEL_OUT_Y_H 0x2B
#define ACCEL_OUT_Z_L 0x2C
#define ACCEL_OUT_Z_H 0x2D

//Microphone
#define MIC_GPIO 26
#define MIC_ADC 0

//switch
#define SWITCH_GPIO 15

//flash
#define RESERVED_PROGRAM_SIZE (1024 * 1024) // 1 MB of 16MB arbitrarily reserved for program
#define PAGE_SIZE_BYTES (256) // 256 bytes per page
#define SECTOR_SIZE_BYTES (4096) // 4 KB per sector