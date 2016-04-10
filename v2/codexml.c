#include "codexml.h"

typedef struct {
    int code;
    char desc[CX_CODE_DESC_SIZE];
} CX_CodeInfo;

CX_CodeInfo g_CX_CodeInfos[CX_CODE_NUM] = {
        {CX_SUCCESS,"Success"},
        {CX_FAILED,"Failed"},
        {CX_MEMERR,"Memory Error!"}
};

char* CX_GetCodeInfo(CX_CODE code){
    CX_CodeInfo* info = g_CX_CodeInfos;
    int i;
    if(code<0 || code >= CX_CODE_NUM){
        return CX_NULL;
    }
    if(info[code].code == code){
        return info[code].desc;
    }
    for(i=0;i<CX_CODE_NUM;i++){
        if(info[i].code == code){
            return info[i].desc;
        }
    }
    return CX_NULL;
}
