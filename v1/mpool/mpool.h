#ifndef __MPOOL_H__
#define __MPOOL_H__

#include <stdint.h>
#include <stdlib.h>

namespace tk {

    const size_t mpool_default_size = 1024*16;
    typedef struct mpool_block_s {
        uint8_t*        last;
        uint8_t*        end;
        mpool_block_s*  next;
    } mpool_block_t;

    typedef struct mpool_large_block_s {
        mpool_large_block_s*    next;
        uint8_t*                data;
    } mpool_large_block_t;

    class mpool {
    private:
        mpool_block_t   d;
        mpool_block_t*  current;
        size_t          max;

        static mpool*   instance;

        mpool();
        mpool(const mpool&);
        mpool&operator=(const mpool&);
    public:
        static mpool* init(size_t n=mpool_default_size);
        static mpool* get();
    };
};

#endif // __MPOOL_H__