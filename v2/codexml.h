#ifndef __CODEXML_H__
#define __CODEXML_H__


#define CX_CODE_DESC_SIZE 128
#define CX_CMD_NAME_SIZE 32

#define CX_NULL (void*)0

typedef int CX_RET;
typedef int CX_CODE;
typedef void* CX_NodePtr;
typedef CX_RET (*CX_CMD_FUNC)(CX_NodePtr node);

typedef enum {
    CX_SUCCESS=0,
    CX_FAILED,
    CX_MEMERR,

    CX_CODE_NUM
};

char* CX_GetCodeInfo(CX_CODE code);

CX_RET CX_Proc(CX_NodePtr node);
CX_RET CX_InstallCmds();
CX_RET CX_UninstallCmds();
CX_CMD_FUNC CX_GetCmdFunc(char* name);

#endif // __CODEXML_H__
