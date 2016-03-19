//
// Created by tkorays on 3/19/16.
//

#include "mem_pool.h"
#include <stdio.h>


int main(){
    mem_pool_t* pool;

    pool = mem_pool_create();
    if(!pool){
        printf("create pool failed!");
        return -1;
    }

    mem_pool_alloc(pool,200);
    printf("blks num: %ld\n", mem_pool_block_num(pool));

    mem_pool_alloc(pool,200);
    printf("blks num: %ld\n", mem_pool_block_num(pool));

    mem_pool_alloc(pool,1000);
    printf("blks num: %ld\n", mem_pool_block_num(pool));

    mem_pool_alloc(pool,1000);
    printf("blks num: %ld\n", mem_pool_block_num(pool));

    mem_pool_destroy(pool);

    return 0;
}