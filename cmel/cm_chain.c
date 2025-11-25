//头文件
#include"cm_chain.h"

//移植接口
//内存分配接口
#include<stdlib.h>
#define ch_malloc(size) malloc(size)
#define ch_free(p) free(p)
//输入输出接口
#include<stdio.h>
#define ch_log(args,...) printf("[CM_LOG][%s:%d:%s]: " args "\n",__FILE__,__LINE__,__func__,##__VA_ARGS__)

//单链表初始化
cm_chain_sll_t* cm_chain_sll_init(void* data);
//单链表插入
cm_chain_sll_t* cm_chain_sll_insert(cm_chain_sll_t* sll, void* data);
//单链表添加
cm_chain_sll_t* cm_chain_sll_add(cm_chain_sll_t* sll, void* data);
//单链表删除
uint8_t cm_chain_sll_del(cm_chain_sll_t* sll);
//单链表反初始化
uint8_t cm_chain_sll_deinit(cm_chain_sll_t* sll);
//单链表成环
uint8_t cm_chain_sll_tocyc(cm_chain_sll_t* head, cm_chain_sll_t* tail);
//单链表去环
uint8_t cm_chain_sll_decyc(cm_chain_sll_t* sll);
//单链表计数
uint32_t cm_chain_sll_count(cm_chain_sll_t* sll);

//单链表初始化
cm_chain_sll_t* cm_chain_sll_init(void* data)
{
    //分配内存
    cm_chain_sll_t* node=(cm_chain_sll_t*)ch_malloc(sizeof(cm_chain_sll_t));
    if(!node)
    {
        ch_log("mem err");
        return NULL;
    }
    //链表连接
    node->data = data;
    node->next = NULL;
    return node;
}

//单链表插入
cm_chain_sll_t* cm_chain_sll_insert(cm_chain_sll_t* sll, void* data)
{
    //有效性检查
    if(!sll)
    {
        ch_log("node inval");
        return NULL;
    }
    //分配内存
    cm_chain_sll_t* node = (cm_chain_sll_t*)ch_malloc(sizeof(cm_chain_sll_t));
    if(!node)
    {
        ch_log("mem err");
        return NULL;
    }
    //链表连接
    if(sll->next)
    {
        node->next = sll->next;
    }else
    {
        node->next = NULL;
    }
    sll->next = node;
    node->data = data;
    return node;
}

//单链表添加
cm_chain_sll_t*cm_chain_sll_add(cm_chain_sll_t* sll, void* data)
{
    //如果节点不存在则自动创建
    if(!sll)
    {
        ch_log("creat node");
        sll=cm_chain_sll_init(data);
        return sll;
    }
    //转跳至链表末端
    cm_chain_sll_t* temp = sll;
    while(temp->next)
    {
        //成环检测
        if(temp->next == sll)
        {
            break;
        }
        temp = temp->next;
    }
    //单链表插入
    cm_chain_sll_t* node = cm_chain_sll_insert(temp, data);
    return node;
}

//单链表删除
uint8_t cm_chain_sll_del(cm_chain_sll_t* sll)
{
    //有效性检查
    if(!sll)
    {
        ch_log("node inval");
        return 1;
    }
    //链表删除
    cm_chain_sll_t* temp = sll;
    sll = sll->next;
    ch_free(temp);
    return 0;
}

//单链表反初始化
uint8_t cm_chain_sll_deinit(cm_chain_sll_t* sll)
{
    //有效性检查
    if(!sll)
    {
        ch_log("node inval");
        return 1;
    }
    //链表删除
    cm_chain_sll_t* temp = sll;
    while(temp)
    {
        cm_chain_sll_t* next = temp->next;
        ch_free(temp);
        temp = next;
    }
    return 0;
}

//单链表成环
uint8_t cm_chain_sll_tocyc(cm_chain_sll_t* head, cm_chain_sll_t* tail)
{
    //有效性检查
    if(!head)
    {
        ch_log("node inval");
        return 1;
    }
    //如果未指定尾节点
    if(!tail)
    {
        //转跳至链表末端
        cm_chain_sll_t* temp = head;
        while(temp->next)
        {
            temp = temp->next;
        }
        //连接成环
        temp->next = head;
    }else
    {
        //连接成环
        tail->next = head;
    }
    return 0;
}

//单链表去环
uint8_t cm_chain_sll_decyc(cm_chain_sll_t* sll)
{
    //有效性检查
    if(!sll)
    {
        ch_log("node inval");
        return 1;
    }
    //转跳至链表末端
    cm_chain_sll_t* temp = sll;
    while(temp->next != sll)
    {
        temp = temp->next;
        //成环检测
        if(!temp)
        {
            ch_log("not a cycle");
            return 1;
        }
    }
    //断开环
    temp->next = NULL;
    return 0;
}

//单链表计数
uint32_t cm_chain_sll_count(cm_chain_sll_t* sll)
{
    uint32_t count = 0;
    //有效性检查
    if(!sll)
    {
        return count;
    }
    ++count;
    //转跳至链表末端
    cm_chain_sll_t* temp = sll;
    while(temp->next)
    {
        ++count;
        //成环检测
        if(temp->next == sll)
        {
            break;
        }
        temp = temp->next;
    }
    return count;
}

//双链表初始化
cm_chain_dll_t* cm_chain_dll_init(void* data);
//双链表插入
cm_chain_dll_t* cm_chain_dll_insert(cm_chain_dll_t* sll, void* data);
//双链表添加
cm_chain_dll_t* cm_chain_dll_add(cm_chain_dll_t* sll, void* data);
//双链表删除
uint8_t cm_chain_dll_del(cm_chain_dll_t* sll);
//双链表反初始化
uint8_t cm_chain_dll_deinit(cm_chain_dll_t* sll);
//双链表成环
uint8_t cm_chain_dll_tocyc(cm_chain_dll_t* head, cm_chain_dll_t* tail);
//双链表去环
uint8_t cm_chain_dll_decyc(cm_chain_dll_t* sll);
//双链表计数
uint32_t cm_chain_dll_count(cm_chain_dll_t* dll);

//双链表初始化
cm_chain_dll_t* cm_chain_dll_init(void* data)
{
    //分配内存
    cm_chain_dll_t* node=(cm_chain_dll_t*)ch_malloc(sizeof(cm_chain_dll_t));
    if(!node)
    {
        ch_log("mem err");
        return NULL;
    }
    //初始化数据
    node->data = data;
    node->last = NULL;
    node->next = NULL;
    return node;
}

//双链表插入
cm_chain_dll_t* cm_chain_dll_insert(cm_chain_dll_t* dll, void* data)
{
    //有效性检查
    if(!dll)
    {
        ch_log("node inval");
        return NULL;
    }
    //分配内存
    cm_chain_dll_t* node = (cm_chain_dll_t*)ch_malloc(sizeof(cm_chain_dll_t));
    if(!node)
    {
        ch_log("mem err");
        return NULL;
    }
    //链表连接
    node->last = dll;
    if(dll->next)
    {
        node->next = dll->next;
    }else
    {
        node->next = NULL;
    }
    dll->next = node;
    node->data = data;
    return node;
}

//双链表添加
cm_chain_dll_t* cm_chain_dll_add(cm_chain_dll_t* dll, void* data)
{
    //如果节点不存在则自动创建
    if(!dll)
    {
        ch_log("creat node");
        dll=cm_chain_dll_init(data);
        return dll;
    }
    //转跳至链表末端
    cm_chain_dll_t* temp = dll;
    while(temp->next)
    {
        temp = temp->next;
    }
    //双链表插入
    cm_chain_dll_t* node = cm_chain_dll_insert(temp, data);
    return node;
}

//双链表删除
uint8_t cm_chain_dll_del(cm_chain_dll_t* dll)
{
    //有效性检查
    if(!dll)
    {
        ch_log("node inval");
        return 1;
    }
    //链表删除
    if(dll->last)
    {
        dll->last->next = dll->next;
    }
    if(dll->next)
    {
        dll->next->last = dll->last;
    }
    ch_free(dll);
    return 0;
}

//双链表反初始化
uint8_t cm_chain_dll_deinit(cm_chain_dll_t* dll)
{
    //有效性检查
    if(!dll)
    {
        ch_log("node inval");
        return 1;
    }
    //链表删除
    cm_chain_dll_t* temp = dll;
    while(temp)
    {
        cm_chain_dll_t* next = temp->next;
        ch_free(temp);
        temp = next;
    }
    return 0;
}

//双链表成环
uint8_t cm_chain_dll_tocyc(cm_chain_dll_t* head, cm_chain_dll_t* tail)
{
    //有效性检查
    if(!head)
    {
        ch_log("node inval");
        return 1;
    }
    //如果未指定尾节点
    if(!tail)
    {
        //转跳至链表末端
        cm_chain_dll_t* temp = head;
        while(temp->next)
        {
            temp = temp->next;
        }
        //连接成环
        temp->next = head;
        head->last = temp;
    }else
    {
        //连接成环
        tail->next = head;
        head->last = tail;
    }
    return 0;
}

//双链表去环
uint8_t cm_chain_dll_decyc(cm_chain_dll_t* dll)
{
    //有效性检查
    if(!dll)
    {
        ch_log("node inval");
        return 1;
    }
    //转跳至链表末端
    cm_chain_dll_t* temp = dll;
    while(temp->next != dll)
    {
        temp = temp->next;
        //成环检测
        if(!temp)
        {
            ch_log("not a cycle");
            return 1;
        }
    }
    //断开环
    temp->next = NULL;
    dll->last = NULL;
    return 0;
}

//双链表计数
uint32_t cm_chain_dll_count(cm_chain_dll_t* dll)
{
    uint32_t count = 0;
    //有效性检查
    if(!dll)
    {
        return count;
    }
    ++count;
    //转跳至链表末端
    cm_chain_dll_t* temp = dll;
    while(temp->next)
    {
        ++count;
        //成环检测
        if(temp->next == dll)
        {
            break;
        }
        temp = temp->next;
    }
    return count;
}
