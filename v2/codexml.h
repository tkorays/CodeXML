#ifndef __CODEXML_H__
#define __CODEXML_H__


#define CX_CODE_DESC_SIZE 128
#define CX_CMD_NAME_SIZE 32

#define CX_NULL (void*)0

typedef int CX_RET;
typedef void* CX_NodePtr;
typedef CX_RET (*CX_CMD_FUNC)(CX_NodePtr node);

typedef enum {
    CX_SUCCESS=0,
    CX_FAILED,
    CX_MEMERR,

    CX_CODE_NUM
} CX_CODE;

typedef struct {
    int code;
    char desc[CX_CODE_DESC_SIZE];
} CX_CodeInfo;

typedef struct {
    char        name[CX_CMD_NAME_SIZE];
    CX_CMD_FUNC func;
} CX_CmdInfo;

extern CX_CodeInfo g_CX_CodeInfos[CX_CODE_NUM];
#define CX_GetCodeInfo(code) g_CX_CodeInfos[(code)]

CX_RET CX_Proc(CX_NodePtr node);
CX_RET CX_InstallCmds();
CX_RET CX_UninstallCmds();
CX_CMD_FUNC CX_GetCmdFunc(char* name);

#endif // __CODEXML_H__
