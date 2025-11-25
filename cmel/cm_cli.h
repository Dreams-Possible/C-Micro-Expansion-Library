#pragma once

#include<stdint.h>
#include"cm_chain.h"

/**
 * @brief 命令行接口结构体
 * @param root 命令链表的根节点
 */
typedef struct cm_cli_t
{
    cm_chain_sll_t* root;
} cm_cli_t;

/**
 * @brief 初始化命令行接口
 * @return 返回新创建的CLI实例指针，失败返回NULL
 */
cm_cli_t*cm_cli_init();

/**
 * @brief 注册命令到CLI
 * @param cli CLI实例指针
 * @param name 命令名称
 * @param func 命令处理函数指针
 * @return 成功返回0，失败返回非0值
 * @note 命令处理函数格式: void func(uint32_t args_num, char *args_ptr[])
 */
uint8_t cm_cli_regist(cm_cli_t*cli, const char *name, void (*func)(uint32_t args_num, char *args_ptr[]));

/**
 * @brief 从CLI注销命令
 * @param cli CLI实例指针
 * @param name 要注销的命令名称
 */
void cm_cli_dereg(cm_cli_t*cli, const char *name);

/**
 * @brief 反初始化CLI实例
 * @param cli 指向CLI实例指针的指针
 * @note 该函数会释放CLI实例及其所有资源
 */
void cm_cli_deinit(cm_cli_t**cli);

/**
 * @brief 执行CLI命令
 * @param cli CLI实例指针
 * @param args_num 参数数量
 * @param args_ptr 参数指针数组
 */
void cm_cli_exec(cm_cli_t*cli, uint32_t args_num, char *args_ptr[]);

/**
 * @brief 解析命令行输入
 * @param input 原始输入字符串
 * @param args_str 存储解析后的参数字符串
 * @param args_ptr 存储参数指针数组
 * @return 返回解析出的参数数量
 * @note 调用者需要负责释放args_str和args_ptr
 */
uint32_t cm_cli_parse(const char* input, char** args_str, char*** args_ptr);

/**
 * @brief 释放命令行解析结果
 * @param args_str 参数字符串
 * @param args_ptr 参数指针数组
 */
void cm_cli_parfree(char* args_str, char** args_ptr);

/**
 * @brief 等待并处理CLI命令
 * @param cli CLI实例指针
 * @note 该函数会进入命令等待循环，直到程序退出
 */
void ci_cmd_wait(cm_cli_t* cli);
