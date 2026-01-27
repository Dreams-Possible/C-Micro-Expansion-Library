#include"cm_cli.h"
#include<string.h>

//移植接口
//内存分配接口
#include<stdlib.h>
#define cli_malloc(size) malloc(size)
#define cli_free(p) free(p)
//输入输出接口
#include<stdio.h>
#define cli_log(args,...) printf("[CM_LOG][%s:%d:%s]: " args "\n",__FILE__,__LINE__,__func__,##__VA_ARGS__)
char* cli_get()
{
    static char buffer[64];
    if(fgets(buffer, sizeof(buffer), stdin) != NULL)
    {
        for(uint32_t f= 0; buffer[f] != '\0'; ++f)
        {
            // 去除换行
            if(buffer[f] == '\n')
            {
                buffer[f] = '\0';
                break;
            }
        }
        return buffer;
    }
    return NULL;
}

//命令结构体
typedef struct cmd_t
{
    char* name;
    void (*func)(uint32_t args_num, char *args_ptr[]);
} cmd_t;

//命令初始化
cm_cli_t*cm_cli_init();
//命令注册
uint8_t cm_cli_regist(cm_cli_t*cli, const char *name, void (*func)(uint32_t args_num, char *args_ptr[]));
//命令注销
void cm_cli_dereg(cm_cli_t*cli, const char *name);
//命令反初始化
void cm_cli_deinit(cm_cli_t**cli);
//命令执行
void cm_cli_exec(cm_cli_t*cli, uint32_t args_num, char *args_ptr[]);
//命令解析
uint32_t cm_cli_parse(const char* input, char** args_str, char*** args_ptr);
//命令解析释放
void cm_cli_parfree(char* args_str, char** args_ptr);
//命令等待
void ci_cmd_wait(cm_cli_t* cli);

//命令初始化
cm_cli_t*cm_cli_init()
{
    cm_cli_t* cmd = (cm_cli_t*)cli_malloc(sizeof(cm_cli_t));
    if(!cmd)
    {
        cli_log("mem err");
        return NULL;
    }
    cmd->root = cm_chain_init(NULL);
    if(!cmd->root)
    {
        cli_log("mem err");
        return NULL;
    }
    return cmd;
}

//命令注册
uint8_t cm_cli_regist(cm_cli_t*cli, const char *name, void (*func)(uint32_t args_num, char *args_ptr[]))
{
    //检查有效性
    if(!cli)
    {
        cli_log("cli inval");
        return 1;
    }
    if(!name)
    {
        cli_log("name inval");
        return 1;
    }
    if(!func)
    {    
        cli_log("func inval");
        return 1;
    }
    //创建命令结构体
    cmd_t* cmd = (cmd_t*)cli_malloc(sizeof(cmd_t));
    if(!cmd)
    {
        cli_log("mem err");
        return 1;
    }
    //保存命令
    cmd->name = (char*)cli_malloc(strlen(name) + 1);
    if(!cmd->name)
    {
        cli_free(cmd);
        cli_log("mem err");
        return 1;
    }
    strcpy(cmd->name, name);
    cmd->func=func;
    //添加命令
    cm_chain_add_tail(cli->root, cmd);
    return 0;
}

//命令注销
void cm_cli_dereg(cm_cli_t*cli, const char *name)
{
    //检查有效性
    if(!cli)
    {
        cli_log("cli inval");
        return;
    }
    if(!name)
    {
        cli_log("name inval");
        return;
    }
    cm_chain_t* node = cli->root;
    uint32_t count = cm_chain_count(cli->root);
    for(uint32_t f = 0; f < count; ++f)
    {
        cmd_t* cmd = (cmd_t*)node->data;
        //跳过根节点
        if(!cmd)
        {
            node = node->next;
            continue;
        }
        //匹配命令名称
        if(strcmp(cmd->name, name)==0)
        {
            //释放命令资源
            cli_free(cmd->name);
            cli_free(cmd);
            cm_chain_delete(node);
            return;
        }
        node = node->next;
    }
}

//命令反初始化
void cm_cli_deinit(cm_cli_t**cli)
{
    cm_chain_t* node = (*cli)->root;
    uint32_t count = cm_chain_count((*cli)->root);
    cli_log("cmd count: %d", count);
    for(uint32_t f = 0; f < count; ++f)
    {
        cmd_t* cmd = (cmd_t*)node->data;
        //跳过根节点
        if(!cmd)
        {
            node = node->next;
            continue;
        }
        //释放命令资源
        cli_free(cmd->name);
        cli_free(cmd);
        node = node->next;
    }
    cm_chain_deinit((*cli)->root);
    free(*cli);
    *cli = NULL;
}

//命令执行
void cm_cli_exec(cm_cli_t*cli, uint32_t args_num, char *args_ptr[])
{
    cm_chain_t* node = cli->root;
    uint32_t count = cm_chain_count(cli->root);
    for(uint32_t f = 0; f < count; ++f)
    {
        cmd_t* cmd = (cmd_t*)node->data;
        //跳过根节点
        if(!cmd)
        {
            // cli_log("skip cmd %f",f);
            node = node->next;
            continue;
        }
        //匹配命令名称
        if(strcmp(cmd->name, args_ptr[0])==0)
        {
            //执行命令函数
            cmd->func(args_num, args_ptr);
            return;
        }
        node = node->next;
    }
    cli_log("no cmd: %s\n", args_ptr[0]);
}

//命令解析
uint32_t cm_cli_parse(const char* input, char** args_str, char*** args_ptr)
{
    //保存输入参数
    char* p = (char*)malloc(strlen(input)+1);
    if(!p)
    {
        cli_log("mem err");
        return 0;
    }
    memset(p, 0, strlen(input)+1);
    strcpy(p, input);
    *args_str = p;
    //记录参数量
    char* temp = p;
    uint32_t args_num = 0;
    while(*temp)
    {
        //跳过空格
        while(*temp == ' ')
        {
            ++temp;
        }
        if(!*temp)
        {
            break;
        }
        //找到参数
        ++args_num;
        //跳过参数
        while(*temp && *temp != ' ')
        {
            ++temp;
        }
    }
    //记录参数
    char** args = (char**)malloc((args_num+1) * sizeof(char*));
    if(!args)
    {
        cli_log("mem err");
        return 0;
    }
    temp = p;
    uint32_t args_count = 0;
    while(*temp && args_count < args_num)
    {
        //跳过前导空格
        while(*temp == ' ')
        {
            ++temp;
        }
        if(!*temp)
        {
            break;
        }
        //记录参数起始位置
        args[args_count] = temp;
        ++args_count;
        //转跳至结尾空格
        while(*temp && *temp != ' ')
        {
            ++temp;
        }
        //截断字符串
        if(*temp)
        {
            *temp = '\0';
            ++temp;
        }
    }
    args[args_num] = NULL;
    *args_ptr = args;
    return args_num;
}

//命令解析释放
void cm_cli_parfree(char* args_str, char** args_ptr)
{
    if(args_str)
    {
        cli_free(args_str);
    }
    if(args_ptr)
    {
        cli_free(args_ptr);
    }
}

//命令等待
void ci_cmd_wait(cm_cli_t* cli)
{
    //有效性检查
    if(!cli)
    {
        cli_log("cli inval");
        return;
    }
    while(1)
    {
        cli_log("> ");
        char* input = cli_get();
        if(!input)
        {
            continue;
        }
        uint32_t args_num = 0;
        char* args_str = NULL;
        char** args_ptr = NULL;
        if (input)
        {
            //退出
            if (strcmp(input, "exit") == 0)
            {
                cli_log("cmd inter exit");
                break;
            }
            //命令解析
            args_num = cm_cli_parse(input, &args_str, &args_ptr);
            if(args_num > 0)
            {
                cm_cli_exec(cli, args_num, args_ptr);
            }else
            {
                cli_log("no cmd input");
            }
            //命令解析释放
            cm_cli_parfree(args_str, args_ptr);
        }
    }
}
