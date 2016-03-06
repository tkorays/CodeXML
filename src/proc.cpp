//
// Created by tkorays on 3/6/16.
//

#include <stdlib.h>
#include <string>

#include "proc.h"
#include "proc_base_func.h"
#include "../3rdparty/tinyxml2/tinyxml2.h"

using namespace ivk;
using namespace tinyxml2;
using namespace std;

std::map<std::string,cmd_func> ivk::gCmdFuncMap;
std::map<std::string,proc_data> ivk::gCmdMemMap;
std::map<std::string,uint32_t> ivk::gBaseTypeMap;

proc_data::proc_data():data(0),size(0),own(false) { }
proc_data::proc_data(uint32_t n) {
    this->own = false;
    this->data = (char*)malloc(n);
    if(this->data){
        this->own = true;
        this->size = n;
    }
}
proc_data::proc_data(char *dt, uint32_t n, bool o):data(dt),size(n),own(o) { }
proc_data::~proc_data() {
    // 需要手动调用函数释放资源
    // 这里释放不好,不好
}
proc_data::proc_data(const proc_data &pd) {
    // 防止多次释放资源(也可以深拷贝解决vector多次析构问题)
    this->data = pd.data;
    this->size = pd.size;
    this->own = false;
}
proc_data& proc_data::operator=(const proc_data &pd) {
    this->data = pd.data;
    this->size = pd.size;
    this->own = false;
    return *this;
}
void proc_data::clear(){
    if(this->own){
        free(this->data);
    }
}

// 需要将本函数注册进去!!名字为proc,这样可以递归执行proc子节点proc
uint32_t ivk::proc_exec(void* el){
    if(!el){
        return proc_exec_null;
    }

    XMLElement* r = (XMLElement*)el;
    XMLElement* e = r->FirstChildElement();
    while(e){
        const char* cmd_name = e->Name();
        map<string,cmd_func>::iterator it = gCmdFuncMap.find(cmd_name);
        if(it==gCmdFuncMap.end()){
            e = e->NextSiblingElement();
            continue;
        }

        uint32_t err = it->second((void*)e);
        if(err != proc_no_err){
            return proc_exec_err;
        }
        e = e->NextSiblingElement();
    }
    return proc_sucess;
}

uint32_t ivk::proc_install(){
    // install mem

    // 创建返回值变量
    gCmdMemMap.insert(pair<string,proc_data>("ret",proc_data(sizeof(uint32_t))));

    // install types
    gBaseTypeMap.insert(pair<string,uint32_t>("char",1));
    gBaseTypeMap.insert(pair<string,uint32_t>("uchar",1));
    gBaseTypeMap.insert(pair<string,uint32_t>("int8",1));
    gBaseTypeMap.insert(pair<string,uint32_t>("uint8",1));
    gBaseTypeMap.insert(pair<string,uint32_t>("int16",2));
    gBaseTypeMap.insert(pair<string,uint32_t>("uint16",2));
    gBaseTypeMap.insert(pair<string,uint32_t>("int32",4));
    gBaseTypeMap.insert(pair<string,uint32_t>("uint32",4));
    gBaseTypeMap.insert(pair<string,uint32_t>("int64",8));
    gBaseTypeMap.insert(pair<string,uint32_t>("uint64",8));

    // install base cmd
    gCmdFuncMap.insert(pair<string,cmd_func>("proc",proc_exec));
    gCmdFuncMap.insert(pair<string,cmd_func>("fopen",ivk::cmd_fopen));
    gCmdFuncMap.insert(pair<string,cmd_func>("fwrite",ivk::cmd_fwrite));
    gCmdFuncMap.insert(pair<string,cmd_func>("fclose",ivk::cmd_fclose));
    gCmdFuncMap.insert(pair<string,cmd_func>("fread",ivk::cmd_fread));
    gCmdFuncMap.insert(pair<string,cmd_func>("malloc",ivk::cmd_malloc));
    gCmdFuncMap.insert(pair<string,cmd_func>("free",ivk::cmd_free));

    return proc_no_err;
}



