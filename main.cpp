#include <iostream>
#include <map>
#include "3rdparty/tinyxml2/tinyxml2.h"
using namespace tinyxml2;
using namespace std;

typedef uint32_t (*func)(void*);
char gMem[1024];
uint32_t gMemFreeStart = 0;
map<string,func> gFuncMap;
map<string,char*> gMemMap;

uint32_t cmd_fopen(void*param){
    cout<<"1) open file"<<endl;
    XMLElement* e = (XMLElement*)param;

    const char* hd = e->Attribute("handle");
    const char* md = e->Attribute("mode");
    const char* fn = e->Attribute("file");
    if(!hd || !md || !fn){
        cout<<"Errror!no attr"<<endl;
        return 0;
    }

    FILE* f = fopen(fn,md);
    memcpy(gMem+gMemFreeStart,f,sizeof(FILE*));
    gMemFreeStart += sizeof(FILE*);

    // 变量名和内存映射关系
    gMemMap.insert(pair<string,char*>(string(hd),(char*)f));

    return 0;
}
uint32_t cmd_fwrite(void* param){
    cout<<"2) write file"<<endl;
    XMLElement* e = (XMLElement*)param;

    const char* hd = e->Attribute("handle");
    const char* dt= e->Attribute("data");
    int sz;
    XMLError err = e->QueryIntAttribute("size",&sz);
    if(!hd || !dt || (err!=XML_NO_ERROR)) {
        cout << "Errror!attr error" << endl;
        return 0;
    }
    FILE* f = (FILE*)gMemMap.find(hd)->second;
    fwrite(dt,sizeof(char),sz,f);

    return 0;
}
uint32_t cmd_fclose(void* param){
    cout<<"3) close file"<<endl;
    XMLElement* e = (XMLElement*)param;
    const char* hd = e->Attribute("handle");
    if(!hd){
        cout<<"Error!Attr error!"<<endl;
        return 0;
    }
    FILE* f = (FILE*)gMemMap.find(hd)->second;
    fclose(f);
    return 0;
}

int main___t() {

    gFuncMap.insert(pair<string,func>("fopen",cmd_fopen));
    gFuncMap.insert(pair<string,func>("fwrite",cmd_fwrite));
    gFuncMap.insert(pair<string,func>("fclose",cmd_fclose));

    XMLDocument doc;
    XMLError err = XML_NO_ERROR;
    err = doc.LoadFile("/Users/tkorays/invoker/task.xml");
    if(err!=XML_NO_ERROR){
        cout<<"Open File Failed"<<endl;
        return 0;
    }

    XMLElement* e = doc.FirstChildElement("proc");
    if(e==0){
        cout<<"root node must be a proc"<<endl;
        return 0;
    }
    e = e->FirstChildElement();
    while(e){
        const char* proc_name = e->Name();

        // 查表获取函数入口
        map<string,func>::iterator it = gFuncMap.find(string(proc_name));
        if(it==gFuncMap.end()){
            cout<<"not found proc function"<<endl;
        }else{
            func f = it->second;
            f((void*)e);
        }
        e = e->NextSiblingElement();
    }
    return 0;
}