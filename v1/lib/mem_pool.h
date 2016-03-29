#ifndef __MEM_POOL_H__
#define __MEM_POOL_H__

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MEM_POOL_BLOCK_DEFAULT_SIZE 1024


typedef struct mem_block_s mem_block_t;
typedef struct mem_pool_s mem_pool_t;

struct mem_block_s {
    char *last;
    char *end;
    mem_block_t *next;
};

struct mem_pool_s {
    mem_block_t *head;
    mem_block_t *current;
};

mem_block_t *mem_block_create();

void mem_block_destroy(mem_block_t *blk);

mem_pool_t *mem_pool_create();

void mem_pool_destroy(mem_pool_t *pool);

void *mem_pool_alloc(mem_pool_t *pool, size_t n);

size_t mem_pool_block_num(mem_pool_t *pool);

#ifdef __cplusplus
}
#endif

#endif // __MEM_POOL_H__