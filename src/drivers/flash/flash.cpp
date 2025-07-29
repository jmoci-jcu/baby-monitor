#include "flash.h"
#include "hardware/flash.h"

using namespace flashDriver;
void writeLog(const std::string& log) {

    

    //get data
    //write to first page
    //write to second page
    //...
    //update pointer

    //write to first page
    //check how many bytes are free
    //check how many bytes we need
    //write x bytes, whichever is lower

    //write to second page
    //check how many bytes are free
    //check how many bytes we need
    //write x bytes, whichever is lower
    
}
std::string readLogs() {
    std::string logs;
    for(int32_t* addr = RESERVED_BASE_ADDRESS; addr < FLASH_POINTER; addr++){
        //iterate over each byte
        logs += ((char)*addr);
    }
}