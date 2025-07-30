#include <string>
#include "hardware/sync.h"

#include "flash.h"
#include "hardware_params.h"

int flashDriver::read(const struct lfs_config *c, lfs_block_t block,lfs_off_t off, void *buffer, lfs_size_t size){
    uint32_t addr = FLASH_BASE + block * c->block_size + off;
    memcpy(buffer,(const void *)addr, size);
    return 0;
}
int flashDriver::prog(const struct lfs_config *c, lfs_block_t block,lfs_off_t off, const void *buffer, lfs_size_t size){
    uint32_t addr = FLASH_RESERVED_PROGRAM_BLOCKS*FLASH_BLOCK_WIDTH_BYTES + block * c->block_size + off; //all program operations will be a multiple of program size
    uint32_t interrupts = save_and_disable_interrupts();
    flash_range_program(addr,(uint8_t*)buffer,size);
    restore_interrupts(interrupts);
    return 0;
}
int flashDriver::erase(const struct lfs_config *c, lfs_block_t block){
    uint32_t addr = FLASH_RESERVED_PROGRAM_BLOCKS*FLASH_BLOCK_WIDTH_BYTES + block * c->block_size;
    uint32_t interrupts = save_and_disable_interrupts();
    flash_range_erase(addr,4096);
    restore_interrupts(interrupts);
    return 0;
}
int flashDriver::sync(const struct lfs_config *c){
    //Our driver is simple. We can do nothing.
    return 0;
}
int flashDriver::writeNewLog(){
    lfs_t lfs;
    lfs_file_t file;

    //we need to mount each time as the device could be connected abruptly
    int err = lfs_mount(&lfs,&cfg);
   // reformat if we can't mount the filesystem
    // this should only happen on the first boot
    if (err) {
        lfs_format(&lfs, &cfg);
        lfs_mount(&lfs, &cfg);
    }

    // read stored value
    char logstr[6];
    logstr[5] = '\0';
    lfs_file_open(&lfs, &file, "logs", LFS_O_RDWR | LFS_O_CREAT);
    volatile lfs_size_t readerr = lfs_file_read(&lfs, &file, &logstr, sizeof(logstr)-1);
    printf("Log read: %s\n", logstr);

    // update log
    logstr[0]='h';
    logstr[1]='e';
    logstr[2]='l';
    logstr[3]='l';
    logstr[4]='o';

    lfs_file_rewind(&lfs, &file);
    lfs_file_write(&lfs, &file, &logstr, sizeof(logstr));

    // remember the storage is not updated until the file is closed successfully
    lfs_file_close(&lfs, &file);

    // release any resources we were using
    lfs_unmount(&lfs);
    return 0;
}
