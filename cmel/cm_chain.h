#pragma once

#include<stdint.h>

// 链表节点结构体
typedef struct cm_chain_t
{
    void* data;
    struct cm_chain_t* last;
    struct cm_chain_t* next;
} cm_chain_t;

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
