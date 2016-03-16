#include <iostream>
#include "mpool.h"
using namespace std;
using namespace tk;

int main() {

    mpool* m = new mpool();

    void* a = m->alloc(1023);
    void* b = m->alloc(1022);
    void* c = m->alloc(8);
    void* d = m->alloc(5);
    void* e = m->bzalloc(1023);

    cout<<m->block_size()<<endl;
    delete m;

    return 0;
}