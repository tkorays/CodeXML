//
// Created by tkorays on 3/6/16.
//

#ifndef INVOKER_PROC_BASE_FUNC_H
#define INVOKER_PROC_BASE_FUNC_H

#include <stdint.h>

namespace ivk {
    // 定义基本操作
    uint32_t cmd_fopen(void* el);
    uint32_t cmd_fwrite(void* el);
    uint32_t cmd_fread(void* el);
    uint32_t cmd_fclose(void* el);
    uint32_t cmd_malloc(void* el);
    uint32_t cmd_free(void* el);
    uint32_t cmd_while(void* el);
};

#endif //INVOKER_PROC_BASE_FUNC_H
