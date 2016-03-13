#include "mpool.h"

namespace tk{
    mpool::instance = 0;

    mpool* mpool::init(size_t n) {
        if(!instance){
            instance = new mpool();

        }
    }

    mpool* mpool::get() {
        if(!instance){
            instance = init();
        }

        return instance;
    }

}