#include "flash.h"
#include "hardware_params.h"

int flashDriver::read(const struct lfs_config *c, lfs_block_t block,lfs_off_t off, void *buffer, lfs_size_t size){
    uint32_t addr = FLASH_BASE + block * c->block_size + off;
    memcpy(buffer,(const void *)addr, size);
    return 0;
}
int flashDriver::prog(const struct lfs_config *c, lfs_block_t block,lfs_off_t off, const void *buffer, lfs_size_t size){
    uint32_t addr = FLASH_RESERVED_PROGRAM_BLOCKS*FLASH_BLOCK_WIDTH_BYTES + block * c->block_size + off; //all program operations will be a multiple of program size
    flash_range_program(addr,(uint8_t*)buffer,size);
    return 0;
}
int flashDriver::erase(const struct lfs_config *c, lfs_block_t block){
    uint32_t addr = FLASH_RESERVED_PROGRAM_BLOCKS*FLASH_BLOCK_WIDTH_BYTES + block * c->block_size;
    flash_range_erase(addr,4096);
    return 0;
}
int flashDriver::sync(const struct lfs_config *c){
    //Our driver is simple. We can do nothing.
    return 0;
}
