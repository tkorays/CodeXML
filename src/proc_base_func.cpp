//
// Created by tkorays on 3/6/16.
//
#include <string>
#include <map>

#include "proc.h"
#include "proc_base_func.h"
#include "../3rdparty/tinyxml2/tinyxml2.h"

using namespace tinyxml2;
using namespace std;

uint32_t ivk::cmd_fopen(void* el){
    XMLElement* e = (XMLElement*)el;

    const char* hd = e->Attribute("handle");
    const char* md = e->Attribute("mode");
    const char* fn = e->Attribute("file");
    if(!hd || !fn){
        return proc_xml_err;
    }

    FILE* f = fopen(fn, md?md:"wr");
    proc_data dt((char*)f, sizeof(FILE*), false);
    gCmdMemMap.insert(pair<string,proc_data>(hd,dt));

    return proc_sucess;
}
uint32_t ivk::cmd_fwrite(void* el){
    XMLElement* e = (XMLElement*)el;

    const char* hd = e->Attribute("handle");
    const char* dt = e->Attribute("data");
    const char* me = e->Attribute("memory");
    const char* nl = e->Attribute("newline");
    int sz;
    XMLError err = e->QueryIntAttribute("size",&sz);
    if(!hd || (!dt && !me)) {
        return proc_xml_err;
    }

    // 确保关闭的句柄存在
    map<string,proc_data>::iterator it = gCmdMemMap.find(hd);
    if(it==gCmdMemMap.end()){
        return proc_exec_err;
    }
    FILE* f = (FILE*)it->second.data;
    if(!f){
        return proc_exec_err;
    }

    // 写内存内容
    if(me){
        // 查找内存
        map<string,proc_data>::iterator itm = gCmdMemMap.find(me);
        if(itm!=gCmdMemMap.end()){
            fwrite(itm->second.data,sizeof(char),itm->second.size,f);
            // 是否换行,二进制中最好不用
            if(nl){
                if(strcmp(nl,"true")==0){
                    fwrite("\n",1,1,f);
                }
            }
            return proc_sucess;
        }
        if(!dt){
            return proc_mem_err;
        }
    }
    if(dt){
        if(err==XML_NO_ERROR){
            return proc_xml_err;
        }
        fwrite(dt,sizeof(char),strlen(dt),f);
        // 是否换行
        if(nl){
            if(strcmp(nl,"true")==0){
                fwrite("\n",1,1,f);
            }
        }
    }else{
        return proc_mem_err;
    }

    return proc_sucess;
}

uint32_t ivk::cmd_fread(void* el){
    XMLElement* e = (XMLElement*)el;

    const char* hd = e->Attribute("handle");
    const char* me = e->Attribute("memory");
    const char* ty = e->Attribute("type");
    int sz=0;
    XMLError er = e->QueryIntAttribute("size",&sz);
    if(!hd || !me){
        return proc_xml_err;
    }

    // 查找文件句柄
    map<string,proc_data>::iterator it = gCmdMemMap.find(hd);
    if(it==gCmdMemMap.end()){
        return proc_mem_err;
    }
    FILE* f = (FILE*)it->second.data;

    // 查找内存
    map<string,proc_data>::iterator itm = gCmdMemMap.find(me);
    if(itm==gCmdMemMap.end()){
        return proc_mem_err;
    }

    // 如果没有指定类型,默认char
    map<string,uint32_t>::iterator itt = gBaseTypeMap.find(ty?ty:"char");
    if(itt==gBaseTypeMap.end()){
        return proc_type_err;
    }
    uint32_t type_size = itt->second;

    // 如果没有指定大小,默认1
    uint32_t type_num = (uint32_t)(er==XML_NO_ERROR?sz:1);

    uint32_t mem_size = type_size*type_num;

    // 真正读取以内存空间大小为准
    if(mem_size>itm->second.size){
        mem_size = itm->second.size;
    }
    uint32_t ret = (uint32_t)fread(itm->second.data,1,mem_size,f);

    // ret内存变量为系统定义,一定存在,除非你干了些什么
    map<string,proc_data>::iterator itr = gCmdMemMap.find("ret");
    if(itr==gCmdMemMap.end()){
        return proc_mem_err;
    }
    // 写入返回大小
    *(uint32_t*)itr->second.data = ret;

    return proc_sucess;
}

uint32_t ivk::cmd_fclose(void* el){
    XMLElement* e = (XMLElement*)el;
    const char* hd = e->Attribute("handle");
    if(!hd){
        return proc_xml_err;
    }

    // 确保关闭的句柄存在
    map<string,proc_data>::iterator it = gCmdMemMap.find(hd);
    if(it==gCmdMemMap.end()){
        return proc_mem_err;
    }
    FILE* f = (FILE*)it->second.data;
    if(!f){
        return proc_exec_err;
    }

    fclose(f);
    it->second.clear();
    gCmdMemMap.erase(hd);

    return proc_sucess;
}

uint32_t ivk::cmd_malloc(void *el) {
    XMLElement* e = (XMLElement*)el;

    const char* me = e->Attribute("memory");
    const char* ty = e->Attribute("type");
    int sz=0;
    XMLError er = e->QueryIntAttribute("size",&sz);
    if(!me){
        return proc_xml_err;
    }
    // 如果没有指定类型,默认char
    map<string,uint32_t>::iterator it = gBaseTypeMap.find(ty?ty:"char");
    if(it==gBaseTypeMap.end()){
        return proc_type_err;
    }
    uint32_t type_size = it->second;

    // 如果没有指定大小,默认1
    uint32_t type_num = (uint32_t)(er==XML_NO_ERROR?sz:1);

    proc_data dt(type_size*type_num);
    gCmdMemMap.insert(pair<string,proc_data>(me,dt));
    return proc_sucess;
}

uint32_t ivk::cmd_free(void *el) {
    XMLElement* e = (XMLElement*)el;

    const char* me = e->Attribute("memory");
    if(!me){
        return proc_xml_err;
    }

    map<string,proc_data>::iterator it = gCmdMemMap.find(me);
    if(it==gCmdMemMap.end()){
        return proc_mem_err;
    }

    // 需要手动释放资源,后期可能考虑用智能指针来管理
    it->second.clear();
    gCmdMemMap.erase(me);

    return proc_sucess;
}