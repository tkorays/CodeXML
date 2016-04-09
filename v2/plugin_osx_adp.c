#include "plugin.h"
#include <dlfcn.h>

PLG_HANDLE osx_load_lib(const char* name){
    return dlopen(name,RTLD_NOW | RTLD_GLOBAL);
}
void osx_close_lib(PLG_HANDLE hd){
    if(hd) dlclose(hd);
}

PLG_HANDLE osx_lib_addr(PLG_HANDLE hd, const char* name){
    return dlsym(hd,name);
}

PLG_DyLibFuncSocket* PLG_AdpInstallDyLib(){
    PLG_DyLibFuncSocket* sock = PLG_GetDyLibFuncSocket();
    sock->LoadLib = osx_load_lib;
    sock->CloseLib = osx_close_lib;
    sock->LibAddr = osx_lib_addr;
    return sock;
}