#include "codexml.h"
#include "mem_pool.h
#include "mem_pool.h"

#include <string.h>

typedef struct {
    char        name[CX_CMD_NAME_SIZE];
    CX_CMD_FUNC func;
} CX_CmdInfo;

typedef struct _CmdInfo {
    CX_CmdInfo          cmd;
    struct _CodeInfo*   next;
} CmdInfo;

typedef struct {
    CmdInfo* first;
    CmdInfo* current;
} CmdInfoList;

CmdInfoList g_CmdList;
mem_pool_t* g_mpool;

// 定义基本函数,对外不可见
CX_RET cmd_load(CX_NodePtr node);
CX_RET cmd_unload(CX_NodePtr node);
CX_RET cmd_call(CX_NodePtr node);

CmdInfo* CreateCmd(char* name, CX_CMD_FUNC func);
void InsertCmd(CmdInfoList* list, char* name, CX_CMD_FUNC func);

CX_RET CX_InstallCmds(){
    CmdInfoList* cmd_list = &g_CmdList;
    g_mpool = mem_pool_create();
    if(!g_mpool){
        return CX_MEMERR;
    }

    InsertCmd(cmd_list, "proc", CX_Proc);
    InsertCmd(cmd_list, "load", cmd_load);
    InsertCmd(cmd_list, "unload", cmd_unload);
    InsertCmd(cmd_list, "call", cmd_call);

    return CX_SUCCESS;
}

CX_CMD_FUNC CX_GetCmdFunc(char* name){
    CmdInfo* cmd = g_CmdList.first;
    while(cmd){
        if(strcmp(cmd->cmd.name,name)==0){
            return cmd->cmd.func;
        }
        cmd = cmd->next;
    }
    return CX_NULL;
}


CmdInfo* CreateCmd(char* name, CX_CMD_FUNC func){
    CmdInfo* cmd = (CmdInfo*)mem_pool_alloc(g_mpool,sizeof(CmdInfo));
    if(!cmd){
        return CX_NULL;
    }

    cmd->next = 0;
    memcpy(cmd->cmd.name,name,strlen(name)+1);
    cmd->cmd.func = func;
    return cmd;
}
void InsertCmd(CmdInfoList* list, char* name, CX_CMD_FUNC func){
    if(!list || !name || !func){
        return ;
    }
    list->current->next = CreateCmd(name,func);
    list->current = list->current->next;
}


