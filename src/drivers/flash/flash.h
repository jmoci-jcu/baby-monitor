#include <string>
#include "pico/stdlib.h"
#include "hardware/flash.h"
#include "hardware_params.h"

#define RESERVED_BASE_ADDRESS (int32_t*)(XIP_BASE + RESERVED_PROGRAM_SIZE)
#define RESERVED_WIDTH (SECTOR_SIZE_BYTES)
#define FLASH_POINTER (int32_t*)(RESERVED_BASE_ADDRESS) //pointer to next unwritten flash address

namespace flashDriver {
    // Function to store log data in flash memory
    //store pointer at base address
    //when pointer reaches end of reserved area, wrap around
    void writeLog(const std::string& log); // write to the next unwritten byte
    std::string readLogs(); // read all bytes within reserved area
}