#include "mpool.h"

#include <string.h>

namespace tk{
    mpool::mpool() {
        char* m = (char*)malloc(mpool_default_size + sizeof(mpool_block_t));
        head = (mpool_block_t*)m;
        head->last = m + sizeof(mpool_block_t);
        head->end = head->last + mpool_default_size;
        head->next = 0;
        current = head;
    }
    mpool::~mpool(){
        mpool_block_t* cur = this->head;
        mpool_block_t* nex;

        while(cur){
            nex = cur->next;
            free(cur);
            cur = nex;
        }
        this->head = 0;
        this->current = 0;
    }
    void mpool::create_new_block() {
        char* m = (char*)malloc(mpool_default_size + sizeof(mpool_block_t));
        mpool_block_t* p = (mpool_block_t*)m;
        p->last = m + sizeof(mpool_block_t);
        p->end = p->last + mpool_default_size;
        p->next = 0;
        current->next = p;
        current = p;
    }

    void* mpool::alloc(size_t n) {
        if(n>mpool_default_size){
            return 0;
        }
        size_t left = current->end - current->last;
        if(n>left){
            create_new_block();
        }
        char* m = current->last;
        current->last += n;
        return m;
    }
    void* mpool::bzalloc(size_t n) {
        void* m = this->alloc(n);
        memset(m,0,n);
        return m;
    }

    size_t mpool::block_size() {
        mpool_block_t* cur = this->head;
        mpool_block_t* nex;
        size_t sz = 0;

        while(cur){
            nex = cur->next;
            sz++;
            cur = nex;
        }
        return sz;
    }

}