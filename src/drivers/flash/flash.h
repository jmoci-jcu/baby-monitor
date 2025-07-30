#pragma once
#include "lfs.h"
#include <string>

#include "hardware_params.h"

namespace flashDriver{

int read(const struct lfs_config *c, lfs_block_t block,lfs_off_t off, void *buffer, lfs_size_t size);
int prog(const struct lfs_config *c, lfs_block_t block,lfs_off_t off, const void *buffer, lfs_size_t size);
int erase(const struct lfs_config *c, lfs_block_t block);
int sync(const struct lfs_config *c);

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

int writeNewLog();

};