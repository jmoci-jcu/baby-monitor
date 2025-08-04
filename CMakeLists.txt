cmake_minimum_required(VERSION 3.13)

# Detect if the active kit is an ARM cross-compiler
if(CMAKE_CXX_COMPILER MATCHES "arm-none-eabi")
    message(STATUS "Detected that the current kit is a cross-compiler.")
    set(CrossCompiling 1)
else()
    message(STATUS "Detected that the current kit is a host compiler. Building the test harness.")
endif()

# Detect if the active kit is an ARM cross-compiler
if(CrossCompiling)
    # Yes, build for the RP2040

    set(CMAKE_C_STANDARD 11)
    set(CMAKE_CXX_STANDARD 17)

    # Specify an increased oscillator startup delay to work around a potential hardware issue where the 
    # clock is slow to boot.
    add_compile_definitions(PICO_XOSC_STARTUP_DELAY_MULTIPLIER=64)

    # Pull in Raspberry Pi Pico SDK (must be before project)
    include(pico_sdk_import.cmake)

    project(cc3501-labs C CXX ASM)
    
    # Initialise the Raspberry Pi Pico SDK
    pico_sdk_init()

    # # Set up CMSIS-DS
    # # set options for which parts of CMSIS-DSP are to be included
    # set(BASICMATH ON)
    # set(COMPLEXMATH ON)
    # set(CONTROLLER OFF)
    # set(FASTMATH OFF)
    # set(FILTERING OFF)
    # set(MATRIX OFF)
    # set(STATISTICS OFF)
    # set(SUPPORT OFF)
    # set(TRANSFORM ON)
    # set(SVM OFF)
    # set(BAYES OFF)
    # set(DISTANCE OFF)
    # set(INTERPOLATION OFF)
    # set(QUATERNIONMATH OFF)
    # set(CONFIGTABLE ON)
    # set(RFFT_Q15_1024 ON) # which FFT constants are hard-coded into the app
    # add_subdirectory(lib/CMSIS-DSP/Source bin_dsp)
    add_library(littlefs STATIC
        libs/littlefs/lfs.c
        libs/littlefs/lfs_util.c
    )

    add_executable(labs)
    target_sources(labs 
        PUBLIC
        src/main.cpp

        src/example_scripts/led_example.cpp
        src/drivers/logging/logging.cpp
        src/drivers/led/led.cpp
        src/drivers/accelerometer/accelerometer.cpp
        src/drivers/microphone/microphone.cpp
        src/monitors/vibrations_alarm.cpp
        src/drivers/flash/flash.cpp
        src/drivers/bluetooth/bluetooth.cpp
        src/IO/uart_terminal/uart_terminal.cpp
        src/sensors/motion.cpp
        src/drivers/HDC2010/hdc2010.cpp
        src/sensors/hdc2010_sensor.cpp
        src/IO/logger/logger.cpp
    )
    target_include_directories(labs
        PUBLIC 
        src/
        libs/littlefs/
    )

    pico_set_program_name(labs "cc3501-labs")
    pico_set_program_version(labs "0.2")

    # select UART for standard IO
    pico_enable_stdio_uart(labs 1)
    pico_enable_stdio_usb(labs 0)

    # compile the PIO file
    pico_generate_pio_header(labs ${CMAKE_CURRENT_LIST_DIR}/src/drivers/WS2812/WS2812.pio)

    # Add the standard library to the build
    target_link_libraries(labs
        #CMSISDSP
        littlefs
        pico_stdlib
        hardware_spi
        hardware_i2c
        hardware_adc
        hardware_dma
        hardware_pio
        hardware_interp
        hardware_timer
        hardware_watchdog
        hardware_clocks
        hardware_pwm
        hardware_flash
        hardware_sync
        hardware_uart
    )


    pico_add_extra_outputs(labs)

else()

    set(CMAKE_C_STANDARD 11)
    set(CMAKE_CXX_STANDARD 20)

    # We are building natively, so create the test harness instead
    project(cc3501-labs CXX)

    add_executable(labs)

    target_link_options(labs PRIVATE -Wl,-u,_printf_float)
    
    target_sources(labs 
        PUBLIC
        src/main.cpp
        src/drivers/led.cpp
        src/drivers/logging/logging.cpp
        tests/mocks/pico/stdlib.cpp
        tests/mocks/pico/time.cpp
        tests/mocks/hardware/gpio.cpp
        tests/mocks/hardware/pio.cpp
        tests/mocks/ws2812.cpp
    )
    add_library(littlefs STATIC
        external/littlefs/lfs.c
        external/littlefs/lfs_util.c
    )
    target_include_directories(labs
        PUBLIC 
        src/
        tests/
        tests/mocks/
        libs/littlefs/
    )
    target_compile_definitions(labs 
        PUBLIC
        TEST_HARNESS=1
    )

endif()

target_compile_definitions(labs 
    PUBLIC
    LOG_DRIVER_STYLE=${LogDriverImplementation}
)
