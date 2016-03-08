//
// Created by tkorays on 3/8/16.
//

#include "memory.h"
#include <stdlib.h>

namespace tk{

    // _data start
    // ************************************************
    _data::_data(uint32_t cap){
        this->used = 0;
        this->data = malloc(cap);
        if(!this->data){
            this->capacity = 0;
            this->owned = false;
        }else{
            this->capacity = cap;
            this->owned = true;
        }
    }

    _data::_data(char *dt, uint32_t cap, bool o) {
        if(!dt){
            this->capacity = 0;
            this->used = 0;
            this->owned = false;
            this->data = 0;
        }else{
            this->capacity = cap;
            this->used = 0;
            this->owned = o;
            this->data = dt;
        }
    }

    _data::_data(const ::tk::_data::_data & dt) {
        this->data = malloc(dt.capacity);
        if(!this->data){
            this->capacity = 0;
            this->used = 0;
            this->owned = true;
        }else{
            memcpy(this->data,dt.data,dt.used);
            this->capacity = dt.capactiy;
            this->used = dt.used;
        }
    }
    // ************************************************
    // _data end

}