//
// Created by tkorays on 3/6/16.
//

#include <stdlib.h>
#include <string>
#include <iostream>

#include "proc.h"
#include "proc_base_func.h"
#include "../3rdparty/tinyxml2/tinyxml2.h"

using namespace ivk;
using namespace tinyxml2;
using namespace std;

std::map<std::string,cmd_func> ivk::gCmdFuncMap;
std::map<std::string,tinyxml2::XMLElement*> ivk::gUserCmdMap;
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

    XMLElement* r = *(XMLElement**)el;
    XMLElement* e = r->FirstChildElement();
    while(e){
        const char* cmd_name = e->Name();

        // 先在系统的cmd函数表中查询
        map<string,cmd_func>::iterator it = gCmdFuncMap.find(cmd_name);
        XMLElement* elements[2];
        elements[0] = e;
        elements[1] = *((XMLElement**)el+1);
        if(it!=gCmdFuncMap.end()){
            uint32_t err = it->second((void*)elements);
            if(err != proc_no_err){
                return proc_exec_err;
            }
            e = e->NextSiblingElement();
            continue;
        }

        // 系统的cmd函数表中没有则查找用户cmd表
        map<string,XMLElement*>::iterator it_user = gUserCmdMap.find(cmd_name);
        if(it_user!=gUserCmdMap.end()){

            // 将当前结点挂载在某个结点上执行
            XMLElement* els[2];
            els[0] = it_user->second;
            els[1] = e;
            proc_exec(els);

            e = e->NextSiblingElement();
            continue;
        }

        e = e->NextSiblingElement();
    }
    return proc_success;
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
    gCmdFuncMap.insert(pair<string,cmd_func>("while",ivk::cmd_while));
    gCmdFuncMap.insert(pair<string,cmd_func>("if",ivk::cmd_if));

    gCmdFuncMap.insert(pair<string,cmd_func>("setret",ivk::cmd_set_ret));

    return proc_no_err;
}

uint32_t ivk::proc_add_cmds(XMLElement* el){
    if(!el){
        return proc_mem_err;
    }

    XMLElement* e = el->FirstChildElement();
    while(e){
        const char* cmd_name = e->Attribute("name");
        if(!cmd_name){
            e = e->NextSiblingElement();
            continue;
        }
        gUserCmdMap.insert(pair<string,XMLElement*>(cmd_name,e));

        e = e->NextSiblingElement();
    }

    return proc_success;
}


const char* ivk::get_attr_val(tinyxml2::XMLElement** el, const char* attr_name){
    if(!el || !attr_name){
        return 0;
    }
    // 先获取自己的value,判断是否以@开头,是的话需要请求父节点
    const char* val = (*el)->Attribute(attr_name);
    if(!val){
        return 0;
    }
    if(val[0]=='@'){
        string n(val);
        string root_name = n.substr(1,n.length());
        // 获取挂载结点
        XMLElement* el_root = *(el+1);
        if(!el_root){
            return 0;
        }
        const char* ret = el_root->Attribute(root_name.c_str());
        return ret;
    }else{
        return val;
    }
}
