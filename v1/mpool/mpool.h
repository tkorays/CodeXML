#ifndef __MPOOL_H__
#define __MPOOL_H__

#include <stdint.h>
#include <stdlib.h>

namespace tk {

    const size_t mpool_default_size = 1024;

    typedef struct mpool_block_s {
        char*        last;
        char*        end;
        mpool_block_s*  next;
    } mpool_block_t;

    class mpool {
    private:
        mpool_block_t*  head;
        mpool_block_t*  current;


        mpool(const mpool&);
        mpool&operator=(const mpool&);

        void create_new_block();
    public:
        mpool();
        ~mpool();
        void* alloc(size_t n);
        void* bzalloc(size_t n);
        size_t block_size();
    };
};

#endif // __MPOOL_H__