#ifndef __PLUGIN_ADP_H__
#define __PLUGIN_ADP_H__

#include "plugin_if.h"

typedef PLG_HANDLE (*PLG_LOAD_LIB_FUNC)(const char* dllname);
typedef void (*PLG_CLOSE_LIB_FUNC)(PLG_HANDLE hd);
typedef PLG_HANDLE (*PLG_LIB_ADDR)(PLG_HANDLE plghd,const char* name);

typedef struct {
    PLG_LOAD_LIB_FUNC LoadLib;
    PLG_CLOSE_LIB_FUNC CloseLib;
    PLG_LIB_ADDR LibAddr;
} PLG_DyLibFuncSocket;

#endif // __PLUGIN_ADP_H__
