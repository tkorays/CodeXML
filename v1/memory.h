//
// Created by tkorays on 3/8/16.
//

#ifndef INVOKER_MEMORY_H
#define INVOKER_MEMORY_H

#include "stdint.h"

namespace tk{
    typedef enum{
        ret_success,
        ret_failed
    };
    // 定义数据,_开头表示内部私有,对外不可用
    class _data {
    private:

        _data&operator=(const _data&);
    public:
        char*     data;      // 内存
        uint32_t  size;      // 内存大小
        bool      owned;     // 是否为自己管理

        _data();
        _data(uint32_t sz);                            // 根据大小创建空间
        _data(char* dt, uint32_t sz, bool o = false);  // 使用该类管理已有内存
        _data(const _data& dt);                        // 拷贝构造,深拷贝防止多次析构
        ~_data();
        bool own(_data& dt);                           // 占有其他data对象的数据


        // 写入一个数据
        uint32_t write(const char* dt, uint32_t tsize, uint32_t offset = 0);
        const char* read(uint32_t tsize, uint32_t offset);
    };

};

#endif //INVOKER_MEMORY_H
