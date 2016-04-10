#include "ixml.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    XML_RET code;
    char    desc[64];
} ErrorInfo;

// by index
ErrorInfo g_ErrInfo[XML_CODE_NUM] = {
        {XML_SUCCESS,"Success"},
        {XML_FAILED,"Failed"},
        {XML_PARA_ERR,"Invalid Param!"},
        {XML_FILE_ERR,"File Error!"},
        {XML_MPOOL_ERR,"Memory Pool Error!"},
        {XML_MPALLOC_ERR,"Memroy Pool Alloc Error!"},
        {XML_MALLOC_ERR,"Memory Alloc Error!"},
        {XML_PARSE_ERR,"Parser Error!"},


        {XML_CODE_ERR,"Error Code Is Not Correct!"}
};



XML_RET XML_ParseFile(const char* filename,XML_Doc_t* doc){
    XML_RET ret;
    char* str = 0;
    long filesize = 0;
    FILE* hFile;

    if(!filename || !doc){
        return XML_PARA_ERR;
    }

    hFile = fopen(filename,"r");
    if(!hFile){
        return XML_FILE_ERR;
    }

    fseek(hFile,0,SEEK_END);
    filesize = ftell(hFile); // big file is not permitted

    str = malloc(filesize);
    if(!str){
        fclose(hFile);
        return XML_MALLOC_ERR;
    }
    fread(str,filesize,1,hFile);
    fclose(hFile);

    ret = XML_ParseString(str,filesize,doc);

    free(str);

    if(ret != XML_SUCCESS){
        return ret;
    }
    return XML_SUCCESS;
}

XML_RET XML_ParseString(const char* str,int size,XML_Doc_t* doc){
    mem_pool_t* mpool;

    if(!str || !doc){
        return XML_PARA_ERR;
    }

    mpool = mem_pool_create();
    if(!mpool){
        return XML_MPOOL_ERR;
    }

    doc = (XML_Doc_t*)mem_pool_alloc(mpool,sizeof(XML_Doc_t));
    if(!doc){
        return XML_MPALLOC_ERR;
    }

    doc->mpool = mpool;
    doc->root = 0;

    return XML_SUCCESS;
}

char* XML_GetErrorInfo(XML_RET code){
    ErrorInfo* ei = g_ErrInfo;
    if(code<XML_CODE_START || code>XML_CODE_NUM){
        return ei[XML_CODE_ERR].desc;
    }
}
