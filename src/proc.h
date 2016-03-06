//
// Created by tkorays on 3/6/16.
//

#ifndef INVOKER_PROC_H
#define INVOKER_PROC_H

#include<map>
#include<string>

namespace ivk {
    typedef uint32_t (*cmd_func)(void* param);
    typedef enum{
        proc_no_err=0,
        proc_sucess=0,
        proc_failed,
        proc_param_err,
        proc_exec_err,
        proc_exec_null,
        proc_xml_err,
        proc_type_err,
        proc_mem_err
    } proc_err;

    // 简单的用于保存传递数据的类
    // 对外开放,注意不要误操作
    class proc_data {
    private:

    public:
        uint32_t size;
        char*    data;
        bool     own;
        proc_data();
        proc_data(uint32_t n);
        proc_data(char* data,uint32_t n,bool o=false);
        ~proc_data();
        proc_data(const proc_data& pd);
        proc_data&operator=(const proc_data& pd);
        void clear();

    };
    extern std::map<std::string,cmd_func> gCmdFuncMap;
    extern std::map<std::string,proc_data> gCmdMemMap;
    extern std::map<std::string,uint32_t> gBaseTypeMap;

    uint32_t proc_exec(void* el);
    uint32_t proc_install();

};

#endif //INVOKER_PROC_H
