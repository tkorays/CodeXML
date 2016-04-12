#include "ixml.h"
#include <stdio.h>

int main(){
    XML_RET ret = XML_SUCCESS;
    XML_Doc_t* doc = 0;
    ret = XML_ParseFile("xml/a.xml",doc);
    if(ret != XML_SUCCESS){
        printf("Error: %s\n",XML_GetErrorInfo(ret));
        return 0;
    }

    XML_Destroy(&doc);
    return 0;
}