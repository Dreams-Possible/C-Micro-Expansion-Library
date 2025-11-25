#pragma once

#include<stdint.h>

/**
 * @brief 单链表节点结构体
 * @param data 节点数据指针
 * @param next 指向下一个节点的指针
 */
typedef struct cm_chain_sll_t
{
    void* data;
    struct cm_chain_sll_t* next;
} cm_chain_sll_t;

/**
 * @brief 初始化单链表
 * @param data 初始节点的数据
 * @return 返回新创建的单链表头节点指针，失败返回NULL
 */
cm_chain_sll_t* cm_chain_sll_init(void* data);

/**
 * @brief 在单链表中插入新节点
 * @param sll 单链表节点指针
 * @param data 要插入的数据
 * @return 返回新插入的节点指针，失败返回NULL
 * @note 新节点会插入到指定节点的后面
 */
cm_chain_sll_t*cm_chain_sll_insert(cm_chain_sll_t* sll, void* data);

/**
 * @brief 在单链表末尾添加新节点
 * @param sll 单链表头节点指针
 * @param data 要添加的数据
 * @return 返回新添加的节点指针，失败返回NULL
 */
cm_chain_sll_t* cm_chain_sll_add(cm_chain_sll_t* sll, void* data);

/**
 * @brief 删除单链表中的节点
 * @param sll 要删除的节点指针
 * @return 成功返回0，失败返回非0值
 * @note 该函数会释放节点内存，但不会释放节点中的数据
 */
uint8_t cm_chain_sll_del(cm_chain_sll_t* sll);

/**
 * @brief 反初始化整个单链表
 * @param sll 单链表头节点指针
 * @return 成功返回0，失败返回非0值
 * @note 该函数会释放整个链表的所有节点内存，但不会释放节点中的数据
 */
uint8_t cm_chain_sll_deinit(cm_chain_sll_t* sll);

/**
 * @brief 将单链表转换为循环链表
 * @param head 单链表头节点指针
 * @param tail 单链表尾节点指针
 * @return 成功返回0，失败返回非0值
 */
uint8_t cm_chain_sll_tocyc(cm_chain_sll_t* head, cm_chain_sll_t* tail);

/**
 * @brief 将循环链表转换为普通单链表
 * @param sll 循环链表节点指针
 * @return 成功返回0，失败返回非0值
 */
uint8_t cm_chain_sll_decyc(cm_chain_sll_t* sll);

/**
 * @brief 计算单链表节点数量
 * @param sll 单链表头节点指针
 * @return 返回链表中的节点数量
 */
uint32_t cm_chain_sll_count(cm_chain_sll_t* sll);

/**
 * @brief 双链表节点结构体
 * @param data 节点数据指针
 * @param last 指向前一个节点的指针
 * @param next 指向下一个节点的指针
 */
typedef struct cm_chain_dll_t
{
    void* data;
    struct cm_chain_dll_t* last;
    struct cm_chain_dll_t* next;
} cm_chain_dll_t;

/**
 * @brief 初始化双链表
 * @param data 初始节点的数据
 * @return 返回新创建的双链表头节点指针，失败返回NULL
 */
cm_chain_dll_t* cm_chain_dll_init(void* data);

/**
 * @brief 在双链表中插入新节点
 * @param dll 双链表节点指针
 * @param data 要插入的数据
 * @return 返回新插入的节点指针，失败返回NULL
 * @note 新节点会插入到指定节点的后面
 */
cm_chain_dll_t* cm_chain_dll_insert(cm_chain_dll_t* dll, void* data);

/**
 * @brief 在双链表末尾添加新节点
 * @param dll 双链表头节点指针
 * @param data 要添加的数据
 * @return 返回新添加的节点指针，失败返回NULL
 */
cm_chain_dll_t* cm_chain_dll_add(cm_chain_dll_t* dll, void* data);

/**
 * @brief 删除双链表中的节点
 * @param dll 要删除的节点指针
 * @return 成功返回0，失败返回非0值
 * @note 该函数会释放节点内存，但不会释放节点中的数据
 */
uint8_t cm_chain_dll_del(cm_chain_dll_t* dll);

/**
 * @brief 反初始化整个双链表
 * @param dll 双链表头节点指针
 * @return 成功返回0，失败返回非0值
 * @note 该函数会释放整个链表的所有节点内存，但不会释放节点中的数据
 */
uint8_t cm_chain_dll_deinit(cm_chain_dll_t* dll);

/**
 * @brief 将双链表转换为循环链表
 * @param head 双链表头节点指针
 * @param tail 双链表尾节点指针
 * @return 成功返回0，失败返回非0值
 */
uint8_t cm_chain_dll_tocyc(cm_chain_dll_t* head, cm_chain_dll_t* tail);

/**
 * @brief 将循环双链表转换为普通双链表
 * @param dll 循环双链表节点指针
 * @return 成功返回0，失败返回非0值
 */
uint8_t cm_chain_dll_decyc(cm_chain_dll_t* dll);

/**
 * @brief 计算双链表节点数量
 * @param dll 双链表头节点指针
 * @return 返回链表中的节点数量
 */
uint32_t cm_chain_dll_count(cm_chain_dll_t* dll);
