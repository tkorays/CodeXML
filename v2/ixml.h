#ifndef __IXML_H__
#define __IXML_H__

#include "mem_pool.h"

typedef struct XML_AttrPair_s XML_AttrPair_t;
typedef struct XML_Node_s XML_Node_t;
typedef struct XML_Doc_s XML_Doc_t;
typedef int XML_Encode;
typedef int XML_Version;

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
    XML_Node_t      root;
    mem_pool_t      mpool;
};

XML_Doc_t*  XML_ParseFile(const char* filename);
XML_Doc_t*  XML_ParseString(const char* str);
void        XML_Destroy(XML_Doc_t** doc);
char*       XML_ToString(XML_Doc_t* doc);

#endif // __IXML_H__