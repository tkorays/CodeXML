//
// Created by tkorays on 3/8/16.
//

#ifndef INVOKER_MEMORY_H
#define INVOKER_MEMORY_H

#include "stdint.h"

namespace tk{

    // 定义数据,_开头表示内部私有,对外不可用
    class _data {
    private:
        // 不允许默认构造函数和复制
        _data();
        _data&operator=(const _data&);
    public:
        char*     data;
        uint32_t  capacity;
        uint32_t  used;
        bool      owned;

        _data(uint32_t cap);  // 根据大小创建空间
        _data(char* dt, uint32_t cap, bool o = false); // 使用该类管理已有内存
        _data(const _data& dt);  // 拷贝构造,深拷贝防止多次析构

    };

};

#endif //INVOKER_MEMORY_H
