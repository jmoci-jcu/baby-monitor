# Summary
This code was designed to run on the BaMon remote baby monitor unit. 

# Remote Unit
Collects climate, sound and movement data to be accesssed by parents remotely. Controlled by an RP2040 microcontroller. The unit operates in Bluetooth mode while connected, else it falls back on a protocol to buffer data locally in flash memory until a Bluetooth connection is established.

![IMG_20251002_094926962_HDR](https://github.com/user-attachments/assets/bcac51c4-720e-4664-97be-e7c04354d3a1)

#### Devices
- Bluetooth communicates with MCU over UART. Transmits data logs and alerts to a Linux hub with the [hub](https://github.com/jmoci-jcu/baby-monitor-motherboard) software installed.
- Microphone is amplified before being recorded by the RP2040s onboard ADC. If the RMS of a sample exceeds the set threshold, an alert is logged.
- Accelerometer communicates with the MCU over I2C. In wearable mode acceleration data is recorded by the MCU and an alert is logged if significant movement is detected.
- PIR motion sensor transmits low or high based on detected movement when the device is mounted on the cot and facing the baby. The MCU logs an alert if movement is detected.
- Humidity sensor communicates with the MCU on the same I2C network as the accelerometer. Humidity data is recoreded at defined intervals and logged.
- Temperature sensor is included in the humidity sensor IC and is recorded an logged identically.
- Flash XIP memory stores the program as well as data and alert logs while Bluetooth is disconnencted. The [littlefs](https://github.com/littlefs-project/littlefs) library was implemented to perform wear leveling as well as simply and safely manage logs.

<img width="814" height="934" alt="image" src="https://github.com/user-attachments/assets/0354c3b8-1fc9-41d9-ade1-8ebedb0b52be" />

# Credits
 * The `src/drivers/WS2812/WS2812.pio` file is an example for the RP2040 provided by the Raspberry Pi foundation, used under the terms of the BSD license. 

