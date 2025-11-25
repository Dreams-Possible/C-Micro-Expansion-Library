# C-Micro-Expansion-Library

C微型扩展库 - 一个轻量级的C语言实用工具库

## 项目简介

C-Micro-Expansion-Library (CMEL) 是一个专为嵌入式系统和资源受限环境设计的轻量级C语言扩展库。该库提供了一系列常用的数据结构和算法实现，具有内存占用小、性能高效、接口简洁的特点。

## 特性

- 🚀 **轻量级设计** - 专为嵌入式系统和资源受限环境优化
- 📦 **模块化架构** - 各模块独立，可按需使用
- 🔧 **简洁API** - 易于学习和使用的接口设计
- 🛡️ **内存安全** - 提供内存管理保护机制
- 📚 **完整文档** - 详细的函数说明和使用示例

## 模块介绍

### 1. 链式数据结构 (cm_chain)

提供单链表和双链表的完整实现，支持循环链表转换。

**主要功能：**
- 单链表 (Singly Linked List)
  - 初始化、插入、添加、删除节点
  - 链表计数、循环链表转换
  - 内存安全释放

- 双链表 (Doubly Linked List) 
  - 双向遍历支持
  - 前后节点操作
  - 循环双链表支持

### 2. 命令行接口 (cm_cli)

轻量级命令行解析器，支持命令注册和执行。

**主要功能：**
- 命令注册和注销
- 命令行参数解析
- 命令执行调度
- 交互式命令行界面

### 3. PID控制器 (cm_pid)

经典的PID和PD控制器实现，适用于控制系统。

**主要功能：**
- PID控制器 (比例-积分-微分)
  - 参数可配置 (Kp, Ki, Kd)
  - 输出限幅保护
  - 积分抗饱和处理

- PD控制器 (比例-微分)
  - 简化版本，适用于不需要积分项的场景
  - 输出限幅支持

## 快速开始

### 编译使用

```c
#include "cmel/cm_chain.h"
#include "cmel/cm_cli.h"
#include "cmel/cm_pid.h"

// 使用链表示例
cm_chain_sll_t* list = cm_chain_sll_init(data);
cm_chain_sll_add(list, new_data);

// 使用CLI示例
cm_cli_t* cli = cm_cli_init();
cm_cli_regist(cli, "test", test_command);

// 使用PID控制器示例
cm_pid_pid_t* pid = cm_pid_pid_init(1.0, 0.1, 0.05);
float output = cm_pid_pid_comput(pid, current_value, current_time);
```

### 构建说明

将 `cmel/` 目录添加到您的编译路径中，并链接相应的源文件：

```bash
gcc -I./cmel your_program.c cmel/cm_chain.c cmel/cm_cli.c cmel/cm_pid.c -o your_program
```

## API文档

### 链式数据结构

#### 单链表操作
- `cm_chain_sll_init()` - 初始化单链表
- `cm_chain_sll_insert()` - 插入节点
- `cm_chain_sll_add()` - 末尾添加节点
- `cm_chain_sll_del()` - 删除节点
- `cm_chain_sll_count()` - 节点计数

#### 双链表操作
- `cm_chain_dll_init()` - 初始化双链表
- `cm_chain_dll_insert()` - 插入节点
- `cm_chain_dll_add()` - 末尾添加节点
- `cm_chain_dll_del()` - 删除节点

### 命令行接口

- `cm_cli_init()` - 初始化CLI实例
- `cm_cli_regist()` - 注册命令
- `cm_cli_exec()` - 执行命令
- `cm_cli_parse()` - 解析命令行输入

### PID控制器

- `cm_pid_pid_init()` - 初始化PID控制器
- `cm_pid_pid_comput()` - PID计算
- `cm_pid_pd_init()` - 初始化PD控制器
- `cm_pid_pd_comput()` - PD计算

## 许可证

本项目采用 GNU General Public License v3.0 开源许可证。详情请参阅 [LICENSE](LICENSE) 文件。

## 贡献

欢迎提交 Issue 和 Pull Request 来改进这个项目！

## 作者

- Dreams-Possible

## 版本历史

- v1.0.0 - 初始版本发布
  - 链式数据结构模块
  - 命令行接口模块  
