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

//链表初始化
cm_chain_t* cm_chain_init(void* data);
//链表获取头节点
cm_chain_t* cm_chain_get_head(cm_chain_t* node);
//链表获取尾节点
cm_chain_t* cm_chain_get_tail(cm_chain_t* node);
//链表计数
uint32_t cm_chain_count(cm_chain_t* node);
//链表向头部添加数据
cm_chain_t* cm_chain_add_head(cm_chain_t* node, void* data);
//链表向尾部添加数据
cm_chain_t* cm_chain_add_tail(cm_chain_t* node, void* data);
//链表插入节点
cm_chain_t* cm_chain_insert(cm_chain_t* node, void* data);
//链表插入节点（索引）
cm_chain_t* cm_chain_insert_index(cm_chain_t* node, uint32_t index, void* data);
//链表删除节点
uint8_t cm_chain_delete(cm_chain_t* node);
//链表反初始化
uint8_t cm_chain_deinit(cm_chain_t* node);
//链表结构显示
void cm_chain_show(cm_chain_t* node);

//链表初始化
cm_chain_t* cm_chain_init(void* data)
{
    //申请内存
    cm_chain_t* node=(cm_chain_t*)ch_malloc(sizeof(cm_chain_t));
    if(!node)
    {
        ch_log("mem err");
        return NULL;
    }
    node->data = data;
    node->last = NULL;
    node->next = NULL;
    return node;
}

//链表获取头节点
cm_chain_t* cm_chain_get_head(cm_chain_t* node)
{
    cm_chain_t*temp=node;
    cm_chain_t*ret=temp;
    while(temp)
    {
        if(!temp->last)
        {
            ret=temp;
        }
        temp = temp->last;
    }
    return ret;
}

//链表获取尾节点
cm_chain_t* cm_chain_get_tail(cm_chain_t* node)
{
    cm_chain_t*temp=node;
    cm_chain_t*ret=temp;
    while(temp)
    {
        if(!temp->next)
        {
            ret=temp;
        }
        temp = temp->next;
    }
    return ret;
}

//链表计数
uint32_t cm_chain_count(cm_chain_t* node)
{
    //获取头节点
    cm_chain_t* head = cm_chain_get_head(node);
    uint32_t count = 0;
    cm_chain_t* temp = head;
    while(temp)
    {
        ++count;
        temp = temp->next;
    }
    return count;
}

//链表向头部添加数据
cm_chain_t* cm_chain_add_head(cm_chain_t* node, void* data)
{
    //有效性检查
    if(!node)
    {
        ch_log("node inval");
        return NULL;
    }
    //申请内存
    cm_chain_t* new_node = (cm_chain_t*)ch_malloc(sizeof(cm_chain_t));
    if(!new_node)
    {
        ch_log("mem err");
        return NULL;
    }
    //初始化数据
    new_node->data = data;
    new_node->last = NULL;
    new_node->next = NULL;
    //获取头节点
    cm_chain_t* head = cm_chain_get_head(node);
    //添加到头节点前
    new_node->next = head;
    head->last = new_node;
    return new_node;
}

//链表向尾部添加数据
cm_chain_t* cm_chain_add_tail(cm_chain_t* node, void* data)
{
    //有效性检查
    if(!node)
    {
        ch_log("node inval");
        return NULL;
    }
    //申请内存
    cm_chain_t* new_node = (cm_chain_t*)ch_malloc(sizeof(cm_chain_t));
    if(!new_node)
    {
        ch_log("mem err");
        return NULL;
    }
    //初始化数据
    new_node->data = data;
    new_node->last = NULL;
    new_node->next = NULL;
    //获取尾节点
    cm_chain_t* tail = cm_chain_get_tail(node);
    //添加到尾节点后
    tail->next = new_node;
    new_node->last = tail;
    return new_node;
}

//链表插入节点
cm_chain_t* cm_chain_insert(cm_chain_t* node, void* data)
{
    //有效性检查
    if(!node)
    {    
        ch_log("node inval");
        return NULL;
    }
    //申请内存
    cm_chain_t* new_node = (cm_chain_t*)ch_malloc(sizeof(cm_chain_t));
    if(!new_node)
    {
        ch_log("mem err");
        return NULL;
    }
    //初始化数据
    new_node->data = data;
    new_node->last = NULL;
    new_node->next = NULL;
    //插入节点
    node->next=new_node;
    new_node->last = node;
    return new_node;
}

//链表插入节点（索引）
cm_chain_t* cm_chain_insert_index(cm_chain_t* node, uint32_t index, void* data)
{
    //有效性检查
    if(!node)
    {    
        ch_log("node inval");
        return NULL;
    }
    //插入到头节点之前
    if(!index)
    {
        return cm_chain_add_head(node, data);
    }
    //获取头节点
    cm_chain_t* head = cm_chain_get_head(node);
    //获取前级节点
    uint32_t count = 0;
    cm_chain_t* temp = head;
    while(temp)
    {
        ++count;
        if(count == index)
        {
            break;
        }
        temp = temp->next;
    }
    //插入节点
    cm_chain_t* new_node = cm_chain_insert(temp, data);    
    return new_node;
}

//链表删除节点
uint8_t cm_chain_delete(cm_chain_t* node)
{
    //有效性检查
    if(!node)
    {
        ch_log("node inval");
        return 1;
    }
    //调整结构
    if(node->last)
    {
        node->last->next = node->next;
    }
    if(node->next)
    {    
        node->next->last = node->last;
    }
    //释放内存
    ch_free(node);
    return 0;
}

//链表反初始化
uint8_t cm_chain_deinit(cm_chain_t* node)
{
    //有效性检查
    if(!node)
    {
        ch_log("node inval");
        return 1;
    }
    //获取头节点
    cm_chain_t* head = cm_chain_get_head(node);
    //释放内存
    cm_chain_t* temp = head;
    while(temp)
    {
        cm_chain_t* next = temp->next;
        ch_free(temp);
        temp = next;
    }
    return 0;
}

//链表结构显示
void cm_chain_show(cm_chain_t* node)
{
    //有效性检查
    if(!node)
    {
        ch_log("node inval");
        return;
    }
    //获取头节点
    cm_chain_t* head = cm_chain_get_head(node);
    cm_chain_t* temp = head;
    uint32_t count = 0;
    //显示结构
    ch_log("chain:\n");
    while(temp)
    {
        ch_log("count: %d, node: %p, data: %p, last: %p, next: %p\n", count, temp, temp->data, temp->last, temp->next);
        temp = temp->next;
        ++count;
    }
    return;
}
