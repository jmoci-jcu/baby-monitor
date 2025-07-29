#include "flash.h"
#include "hardware/flash.h"

using namespace flashDriver;
void writeLog(const std::string& log) {
    // flash_range_program(*FLASH_POINTER, (const uint8_t*)log.c_str(), log.size());
    // uint32_t flash_pointer_32 = *FLASH_POINTER + log.size();
    // uint8_t flash_pointer[4];
    // flash_pointer[0] = (flash_pointer_32 >> 0) & 0xFF;
    // flash_pointer[1] = (flash_pointer_32 >> 8) & 0xFF;
    // flash_pointer[2] = (flash_pointer_32 >> 16) & 0xFF;
    // flash_pointer[3] = (flash_pointer_32 >> 24) & 0xFF;
    // flash_range_program(RESERVED_BASE_ADDRESS, flash_pointer, sizeof(flash_pointer));
    
    //program first page
    //program second page if needed

    //read in first page
    // char page0[PAGE_SIZE_BYTES];
    // for(int i = 0; i < PAGE_SIZE_BYTES; i++){
    //     page0[i] = *(RESERVED_BASE_ADDRESS+i);
    // }

    // int32_t data_page_index = (int32_t)FLASH_POINTER / 256;
    // int16_t data_page_sub_index = (int32_t)FLASH_POINTER % 256;

    // if(data_page_index == 1){
    //     page0[data_page_sub_index] = 
    // }

    for(int32_t byte_index = 0; byte_index < log.size(); byte_index++){
        int32_t* pointer_address = FLASH_POINTER + byte_index;
        int32_t pointer_page_index = (int32_t)pointer_address/256;
        int32_t pointer_page_sub_index = (int32_t)pointer_address%256;
    }
    
}
std::string readLogs() {
    std::string logs;
    for(int32_t* addr = RESERVED_BASE_ADDRESS; addr < FLASH_POINTER; addr++){
        //iterate over each byte
        logs += ((char)*addr);
    }
}