#include "plugin.h"

int main() {
    PLG_AdpInstallDyLib();
    PLG_HANDLE hd = PLG_LoadLib("sample.dylib");
    PLG_FUNC hello = PLG_GetFunc(hd,"hello");
    hello("");
    PLG_CloseLib(hd);

    return 0;
}