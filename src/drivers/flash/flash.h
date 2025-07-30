#include "lfs.h"

#include "hardware_params.h"

namespace flashDriver{
int read(const struct lfs_config *c, lfs_block_t block,lfs_off_t off, void *buffer, lfs_size_t size);
int prog(const struct lfs_config *c, lfs_block_t block,lfs_off_t off, const void *buffer, lfs_size_t size);
int erase(const struct lfs_config *c, lfs_block_t block);
int sync(const struct lfs_config *c);
};