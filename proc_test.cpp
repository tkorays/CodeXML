//
// Created by tkorays on 3/6/16.
//
#include <cstdint>
#include <map>
#include <iostream>

#include "src/proc.h"
#include "3rdparty/tinyxml2/tinyxml2.h"


using namespace std;
using namespace ivk;
using namespace tinyxml2;

uint32_t cmd_a(void* p){
    cout<<"exec cmd a"<<endl;
    return 0;
}
uint32_t cmd_b(void* p){
    cout<<"exec cmd b"<<endl;
    return 0;
}

uint32_t dump(void* p){
    XMLElement* e = (XMLElement*)p;

    const char* me = e->Attribute("memory");
    if(!me){
        return proc_xml_err;
    }
    // 查找内存
    map<string,proc_data>::iterator itm = gCmdMemMap.find(me);
    if(itm==gCmdMemMap.end()){
        return proc_mem_err;
    }
    char* data = itm->second.data;
    uint32_t size = itm->second.size;
    for(int i=0;i<size;i++){
        cout<<(int)data[i]<<",";
    }
    cout<<endl;
    return proc_sucess;
}

int main(){
    XMLDocument doc;
    XMLError err = XML_NO_ERROR;
    err = doc.LoadFile("/Users/tkorays/invoker/task.xml");
    if(err!=XML_NO_ERROR){
        cout<<"Open File Failed"<<endl;
        return 0;
    }

    // 任务入口
    XMLElement* e = doc.FirstChildElement("proc");
    if(e==0){
        cout<<"root node must be a proc"<<endl;
        return 0;
    }

    proc_install();
    gCmdFuncMap.insert(pair<string,cmd_func>("cmd_a",cmd_a));
    gCmdFuncMap.insert(pair<string,cmd_func>("cmd_b",cmd_b));
    gCmdFuncMap.insert(pair<string,cmd_func>("dump",dump));
    proc_exec(e);

    return 0;
}