#pragma once

#include <stdint.h>

/* 类型声明 */
typedef struct cm_pid_ppid_t cm_pid_ppid_t;  /* 位置式PID控制器 */
typedef struct cm_pid_ppd_t cm_pid_ppd_t;    /* 位置式PD控制器 */
typedef struct cm_pid_ipid_t cm_pid_ipid_t;  /* 增量式PID控制器 */
typedef struct cm_pid_ipi_t cm_pid_ipi_t;    /* 增量式PI控制器 */

/* 以下为位置式PID控制函数声明 */

/* 位置式PID初始化 */
cm_pid_ppid_t* cm_pid_ppid_init();

/* 位置式PID设置目标 */
void cm_pid_ppid_set_target(cm_pid_ppid_t* pid, float target);

/* 位置式PID设置KP */
void cm_pid_ppid_set_kp(cm_pid_ppid_t* pid, float kp);

/* 位置式PID设置KI */
void cm_pid_ppid_set_ki(cm_pid_ppid_t* pid, float ki);

/* 位置式PID设置KD */
void cm_pid_ppid_set_kd(cm_pid_ppid_t* pid, float kd);

/* 设置输出限幅 */
void cm_pid_ppid_set_limit(cm_pid_ppid_t* pid, float min, float max);

/* 位置式PID重置 */
void cm_pid_ppid_reset(cm_pid_ppid_t* pid);

/* 位置式PID反初始化 */
void cm_pid_ppid_deinit(cm_pid_ppid_t** pid);

/* 位置式PID计算 */
float cm_pid_ppid_comput(cm_pid_ppid_t* pid, float input, float time);

/* 以下为位置式PD控制函数声明 */

/* 位置式PD初始化 */
cm_pid_ppd_t* cm_pid_ppd_init();

/* 位置式PD设置目标 */
void cm_pid_ppd_set_target(cm_pid_ppd_t* pd, float target);

/* 位置式PD设置KP */
void cm_pid_ppd_set_kp(cm_pid_ppd_t* pd, float kp);

/* 位置式PD设置KD */
void cm_pid_ppd_set_kd(cm_pid_ppd_t* pd, float kd);

/* 设置输出限幅 */
void cm_pid_ppd_set_limit(cm_pid_ppd_t* pd, float min, float max);

/* 位置式PD重置 */
void cm_pid_ppd_reset(cm_pid_ppd_t* pd);

/* 位置式PD反初始化 */
void cm_pid_ppd_deinit(cm_pid_ppd_t** pd);

/* 位置式PD计算 */
float cm_pid_ppd_comput(cm_pid_ppd_t* pd, float input, float time);

/* 以下为增量式PID控制函数声明 */

/* 增量式PID初始化 */
cm_pid_ipid_t* cm_pid_ipid_init();

/* 增量式PID设置目标 */
void cm_pid_ipid_set_target(cm_pid_ipid_t* pid, float target);

/* 增量式PID设置KP */
void cm_pid_ipid_set_kp(cm_pid_ipid_t* pid, float kp);

/* 增量式PID设置KI */
void cm_pid_ipid_set_ki(cm_pid_ipid_t* pid, float ki);

/* 增量式PID设置KD */
void cm_pid_ipid_set_kd(cm_pid_ipid_t* pid, float kd);

/* 增量式PID设置上次输出 */
void cm_pid_ipid_set_output(cm_pid_ipid_t* pid, float output);

/* 设置输出限幅 */
void cm_pid_ipid_set_limit(cm_pid_ipid_t* pid, float min, float max);

/* 增量式PID重置 */
void cm_pid_ipid_reset(cm_pid_ipid_t* pid);

/* 增量式PID反初始化 */
void cm_pid_ipid_deinit(cm_pid_ipid_t** pid);

/* 增量式PID计算 */
float cm_pid_ipid_comput(cm_pid_ipid_t* pid, float input, float time);

/* 以下为增量式PI控制函数声明 */

/* 增量式PI初始化 */
cm_pid_ipi_t* cm_pid_ipi_init();

/* 增量式PI设置目标 */
void cm_pid_ipi_set_target(cm_pid_ipi_t* pid, float target);

/* 增量式PI设置KP */
void cm_pid_ipi_set_kp(cm_pid_ipi_t* pid, float kp);

/* 增量式PI设置KI */
void cm_pid_ipi_set_ki(cm_pid_ipi_t* pid, float ki);

/* 增量式PI设置KD */
void cm_pid_ipi_set_kd(cm_pid_ipi_t* pid, float kd);

/* 增量式PI设置上次输出 */
void cm_pid_ipi_set_output(cm_pid_ipi_t* pid, float output);

/* 设置输出限幅 */
void cm_pid_ipi_set_limit(cm_pid_ipi_t* pid, float min, float max);

/* 增量式PI重置 */
void cm_pid_ipi_reset(cm_pid_ipi_t* pid);

/* 增量式PI反初始化 */
void cm_pid_ipi_deinit(cm_pid_ipi_t** pid);

/* 增量式PI计算 */
float cm_pid_ipi_comput(cm_pid_ipi_t* pid, float input, float time);
