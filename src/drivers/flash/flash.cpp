#include <string>
#include "hardware/sync.h"

#include "flash.h"
#include "hardware_params.h"
#include "hardware/flash.h"

#define MAX_READ_DEPTH_BYTES 16384 //16kB

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
    //Our driver is simple. We dont need to do anything.
    return 0;
}
std::string flashDriver::flushLogs(){
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
    lfs_file_open(&lfs, &file, "logs", LFS_O_RDWR | LFS_O_CREAT);
    

    //Read entire logs file and print to putty
    std::string fileContents;
    for(int i = 0; i<MAX_READ_DEPTH_BYTES; i++){
        if(i==MAX_READ_DEPTH_BYTES-1){
            printf("Error : Could not read file (could not find end of file).\n");
            break;
        }
        uint8_t readByte;
        lfs_ssize_t readCount = lfs_file_read(&lfs, &file, &readByte, 1);
        if(!readCount){
            break;
        }
        fileContents+=readByte;
    }

    lfs_file_truncate(&lfs,&file,0);

    // remember the storage is not updated until the file is closed successfully
    lfs_file_close(&lfs, &file);

    // release any resources we were using
    lfs_unmount(&lfs);

    return fileContents;
}

int flashDriver::writeNewLog(std::string log){
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
    lfs_file_open(&lfs, &file, "logs", LFS_O_RDWR | LFS_O_CREAT);
    
    // Store log in flash

    //find end of contents
    for(int i =0; i < MAX_READ_DEPTH_BYTES; i++){
        uint8_t readByte;
        lfs_ssize_t readCount = lfs_file_read(&lfs, &file, &readByte, 1);
        if(readCount == 0){
            lfs_file_seek(&lfs,&file,i,LFS_SEEK_SET);
            break;
        }
    }
    uint8_t readString[log.length()];
    for(int i = 0; i<log.length(); i++){
        readString[i] = log.c_str()[i];
    }

    lfs_file_write(&lfs, &file, &readString, sizeof(readString));

    // remember the storage is not updated until the file is closed successfully
    lfs_file_close(&lfs, &file);

    // release any resources we were using
    lfs_unmount(&lfs);
    
    return 0;
}
