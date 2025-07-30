#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include <array>
#include "WS2812.pio.h" // This header file gets produced during compilation from the WS2812.pio file
#include "drivers/logging/logging.h"
#include "lfs.h"

#include "hardware_params.h"

#include "example_scripts/led_example.h"
#include "example_scripts/accelerometer_example.h"

#include "IO/logger/logger.h"
#include "drivers/flash/flash.h"

using namespace logger;
using namespace flashDriver;


int main(){

   stdio_init_all();
   lfs_t lfs;
   lfs_file_t file;

       // configuration of the filesystem is provided by this struct
    const struct lfs_config cfg = {
    // block device operations
    .read  = read,
    .prog  = prog,
    .erase = erase,
    .sync  = sync,

    // block device configuration
    .read_size = 1,
    .prog_size = FLASH_PAGE_WIDTH_BYTES,
    .block_size = FLASH_BLOCK_WIDTH_BYTES,
    .block_count = 4096 - FLASH_RESERVED_PROGRAM_BLOCKS,
    .block_cycles = 500,
    .cache_size = FLASH_BLOCK_WIDTH_BYTES,
    .lookahead_size = 64,
    };

   int err = lfs_mount(&lfs,&cfg);

   // reformat if we can't mount the filesystem
    // this should only happen on the first boot
    if (err) {
        lfs_format(&lfs, &cfg);
        lfs_mount(&lfs, &cfg);
    }

    // read current count
    uint32_t boot_count = 0;
    lfs_file_open(&lfs, &file, "boot_count", LFS_O_RDWR | LFS_O_CREAT);
    lfs_file_read(&lfs, &file, &boot_count, sizeof(boot_count));

    // update boot count
    boot_count += 1;
    lfs_file_rewind(&lfs, &file);
    lfs_file_write(&lfs, &file, &boot_count, sizeof(boot_count));

    // remember the storage is not updated until the file is closed successfully
    lfs_file_close(&lfs, &file);

    // release any resources we were using
    lfs_unmount(&lfs);

    // print the boot count
    printf("boot_count: %d\n", boot_count);

   return 0;
}