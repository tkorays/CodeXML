#include "plugin_if.h"
#include <stdio.h>

PLG_HANDLE hello(const char* para){
    printf("hello\n");
    return PLG_NULL;
}
PLG_HANDLE world(const char* para){
    printf("world\n");
    return PLG_NULL;
}

PLG_REG_BEGIN(2)
    PLG_REG_FUNC("hello",hello)
    PLG_REG_FUNC("world",world)
PLG_REG_END()