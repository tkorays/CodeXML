#include "plugin.h"
#include <string.h>


PLG_DyLibFuncSocket* PLG_GetDyLibFuncSocket(){
    static PLG_DyLibFuncSocket sock;
    return &sock;
}

PLG_HANDLE PLG_LoadLib(const char* dllname){
    PLG_DyLibFuncSocket* sock = PLG_GetDyLibFuncSocket();
    if(sock->LoadLib){
        return sock->LoadLib(dllname);
    }
    return PLG_NULL;
}

void PLG_CloseLib(PLG_HANDLE hd){
    PLG_DyLibFuncSocket* sock = PLG_GetDyLibFuncSocket();
    if(sock->CloseLib){
        sock->CloseLib(hd);
    }
}

PLG_HANDLE PLG_LibAddr(PLG_HANDLE hd,const char* name){
    PLG_DyLibFuncSocket* sock = PLG_GetDyLibFuncSocket();
    if(sock->LibAddr){
        return sock->LibAddr(hd,name);
    }
    return PLG_NULL;
}

PLG_FUNC PLG_GetFunc(PLG_HANDLE plghd, const char* name){
    PLG_DyLibFuncSocket* sock = PLG_GetDyLibFuncSocket();
    PLG_FUNC_INFO* func = (PLG_FUNC_INFO*)sock->LibAddr(plghd,PLG_FUNC_INFO_NAME);
    int* size = (int*)sock->LibAddr(plghd,PLG_FUNC_SIZE_NAME);
    int i = 0;

    if(!func || !size || *size<=0){
        return PLG_NULL;
    }

    for(i = 0; i<*size; i++){
        if(strcmp(func[i].name,name)==0){
            return func[i].func;
        }
    }
    return PLG_NULL;
}
