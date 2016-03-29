#include "mem_pool.h"
#include <stdlib.h>

mem_block_t* mem_block_create(){
    char*           m;
    mem_block_t*    blk;

    m = (char*)malloc(MEM_POOL_BLOCK_DEFAULT_SIZE + sizeof(mem_block_t));
    if(!m){
        return 0;
    }

    blk = (mem_block_t*)m;
    blk->last = m + sizeof(mem_block_t);
    blk->end = m + MEM_POOL_BLOCK_DEFAULT_SIZE + sizeof(mem_block_t);
    blk->next = 0;
    return blk;
}

void mem_block_destroy(mem_block_t* blk){
    if(blk){
        free(blk);
    }
}

mem_pool_t* mem_pool_create(){
    mem_pool_t*     pool;
    mem_block_t*    blk;

    pool = (mem_pool_t*)malloc(sizeof(mem_pool_t));
    if(!pool){
        return 0;
    }

    blk = mem_block_create();
    if(!blk){
        free(pool);
        return 0;
    }

    pool->head      = blk;
    pool->current   = blk;

    return pool;
}

void mem_pool_destroy(mem_pool_t* pool){
    mem_block_t*     cur;
    mem_block_t*    next;

    if(!pool){
        return;
    }

    cur = pool->head;
    while(cur){
        next = cur->next;
        mem_block_destroy(cur);
        cur = next;
    }

    free(pool);
}

void* mem_pool_alloc(mem_pool_t* pool, size_t n){
    char*           m;
    int             is_size_valid;
    int             left_size;
    mem_block_t*    blk;
    uintptr_t       addr;

    is_size_valid = ( n<=0 )||(n > MEM_POOL_BLOCK_DEFAULT_SIZE);
    if(!pool || !pool->current || is_size_valid){
        return 0;
    }

    addr = ADDR_ALIGN(pool->current->last,ALIGN_SIZE);
    left_size = pool->current->end - addr; /* may <= 0 */
    if(n > left_size){
        blk = mem_block_create();
        if(!blk){
            return 0;
        }

        pool->current->next = blk;
        pool->current = blk;
        m = blk->last;
        blk->last += n;
        return m;
    }

    // use current left room
    m = pool->current->last;
    pool->current->last += n;
    return m;
}


size_t mem_pool_block_num(mem_pool_t* pool){
    mem_block_t*    blk;
    size_t          cnt = 0;
    if(!pool){
        return 0;
    }
    blk = pool->head;
    while(blk){
        cnt++;
        blk = blk->next;
    }
    return cnt;
}