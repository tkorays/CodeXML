//
// Created by tkorays on 3/8/16.
//

#include "memory.h"
#include <stdlib.h>
#include <string.h>
using namespace std;

namespace tk{

    // _data start
    // ************************************************
    _data::_data():data(0),size(0),owned(0) {
    }

    _data::_data(uint32_t sz){
        this->data = (char*)malloc(sz);
        if(!this->data){
            this->size = 0;
            this->owned = false;
        }else{
            this->size = sz;
            this->owned = true;
        }
    }

    _data::_data(char *dt, uint32_t sz, bool o) {
        if(!dt){
            this->size = 0;
            this->owned = false;
            this->data = 0;
        }else{
            this->size = sz;
            this->owned = o;
            this->data = dt;
        }
    }

    _data::_data(const ::tk::_data & dt) {
        this->data = (char*)malloc(dt.size);
        if(!this->data){
            this->size = 0;
            this->owned = false;
        }else{
            memcpy(this->data,dt.data,dt.size);
            this->size = dt.size;
            this->owned = true;
        }
    }

    _data::~_data() {
        if(this->owned){
            free(this->data);
        }
    }

    // 对于已经管理了内存的对象不允许占有其他对象内存
    bool _data::own(_data &dt) {
        if(this->owned){
            return false;
        }
        if(dt.owned){
            this->data = dt.data;
            this->size = dt.size;
            this->owned = true;

            dt.owned = false;
            dt.data = 0;
            dt.size = 0;
            return true;
        }
        this->owned = false;
        return false;
    }

    uint32_t _data::write(const char* dt, uint32_t tsize, uint32_t offset){
        if(!dt || !this->data || ((offset+1)*tsize>this->size) ){
            return ret_failed;
        }
        memcpy(this->data + offset*tsize, dt, tsize);
        return ret_success;
    }
    const char* _data::read(uint32_t tsize, uint32_t offset) {
        if(!this->data || (offset+1)*tsize>this->size){
            return 0;
        }
        return data + offset*tsize;
    }
    // ************************************************
    // _data end


}