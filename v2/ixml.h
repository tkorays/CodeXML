#ifndef __IXML_H__
#define __IXML_H__

#include "mem_pool.h"

typedef struct XML_AttrPair_s XML_AttrPair_t;
typedef struct XML_Node_s XML_Node_t;
typedef struct XML_Doc_s XML_Doc_t;
typedef int XML_Encode;
typedef int XML_Version;
typedef int XML_RET;
typedef char* XML_STR_OUT;
typedef const char* XML_STR_IN;

typedef enum {
    XML_CODE_START = 0,
    XML_SUCCESS = 0,
    XML_FAILED,
    XML_PARA_ERR,
    XML_FILE_ERR,
    XML_MPOOL_ERR,
    XML_MPALLOC_ERR,
    XML_MALLOC_ERR,
    XML_PARSE_ERR,

    XML_CODE_ERR,
    XML_CODE_NUM
};

struct XML_AttrPair_s {
    char*           name;
    char*           value;
    XML_AttrPair_t* next;
} ;

struct XML_Node_s {
    char*           name;
    char*           text;
    XML_AttrPair_t* attrs;
    XML_Node_t*     parent;
    XML_Node_t*     child;
    XML_Node_t*     next;
};

struct XML_Doc_s {
    XML_Version     version;
    XML_Encode      encode;
    XML_Node_t*     root;
    mem_pool_t*     mpool;
};

XML_RET XML_ParseFile(const char* filename, XML_Doc_t* doc);
XML_RET XML_ParseString(const char* str,int size, XML_Doc_t* doc);
XML_RET XML_Destroy(XML_Doc_t** doc);
XML_RET XML_ToString(XML_Doc_t* doc, char* str, int size);
XML_RET XML_GetAttr(XML_Node_t* node,const char* name, char* value);
XML_RET XML_GetIntAttr(XML_Node_t* node, const char* name, int* value);
char*   XML_GetErrorInfo(XML_RET code);

#endif // __IXML_H__