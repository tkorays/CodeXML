#ifndef __PLUGIN_H__
#define __PLUGIN_H__

#include "plugin_if.h"
#include "plugin_adp.h"

PLG_DyLibFuncSocket* PLG_GetDyLibFuncSocket();
PLG_DyLibFuncSocket* PLG_AdpInstallDyLib();

PLG_HANDLE PLG_LoadLib(const char* name);
void PLG_CloseLib(PLG_HANDLE hd);
PLG_HANDLE PLG_LibAddr(PLG_HANDLE hd,const char* name);
PLG_FUNC PLG_GetFunc(PLG_HANDLE hd, const char* name);

#endif // __PLUGIN_H__