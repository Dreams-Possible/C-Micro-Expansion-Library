#pragma once

#include<stdint.h>

/**
 * @brief PID控制器结构体
 * @param kp 比例系数
 * @param ki 积分系数
 * @param kd 微分系数
 * @param target 目标值
 * @param output_min 输出最小值限制
 * @param output_max 输出最大值限制
 * @param sum_integral 积分项累计值
 * @param last_error 上一次误差值
 * @param last_time 上一次计算时间
 */
typedef struct cm_pid_pid_t
{
    float kp;
    float ki;
    float kd;
    float target;
    float output_min;
    float output_max;
    float sum_integral;
    float last_error;
    float last_time;
} cm_pid_pid_t;

/**
 * @brief 初始化PID控制器
 * @param kp 比例系数
 * @param ki 积分系数
 * @param kd 微分系数
 * @return 返回新创建的PID控制器指针，失败返回NULL
 */
cm_pid_pid_t* cm_pid_pid_init(float kp, float ki, float kd);

/**
 * @brief 设置PID控制器目标值
 * @param pid PID控制器指针
 * @param target 目标值
 */
void cm_pid_pid_set_target(cm_pid_pid_t* pid, float target);

/**
 * @brief 单独设置PID控制器的比例系数
 * @param pid PID控制器指针
 * @param kp 新的比例系数
 */
void cm_pid_pid_set_kp(cm_pid_pid_t* pid, float kp);

/**
 * @brief 单独设置PID控制器的积分系数
 * @param pid PID控制器指针
 * @param ki 新的积分系数
 */
void cm_pid_pid_set_ki(cm_pid_pid_t* pid, float ki);

/**
 * @brief 单独设置PID控制器的微分系数
 * @param pid PID控制器指针
 * @param kd 新的微分系数
 */
void cm_pid_pid_set_kd(cm_pid_pid_t* pid, float kd);

/**
 * @brief 设置PID控制器输出限幅
 * @param pid PID控制器指针
 * @param min 输出最小值
 * @param max 输出最大值
 */
void cm_pid_pid_set_limit(cm_pid_pid_t* pid, float min, float max);

/**
 * @brief 反初始化PID控制器
 * @param pid 指向PID控制器指针的指针
 * @note 该函数会释放PID控制器内存
 */
void cm_pid_pid_deinit(cm_pid_pid_t**pid);

/**
 * @brief PID控制器计算
 * @param pid PID控制器指针
 * @param input 当前输入值
 * @param time 当前时间
 * @return 返回PID计算输出值
 */
float cm_pid_pid_comput(cm_pid_pid_t* pid, float input, float time);

/**
 * @brief PD控制器结构体
 * @param kp 比例系数
 * @param kd 微分系数
 * @param target 目标值
 * @param output_min 输出最小值限制
 * @param output_max 输出最大值限制
 * @param last_error 上一次误差值
 * @param last_time 上一次计算时间
 */
typedef struct cm_pid_pd_t
{
    float kp;
    float kd;
    float target;
    float output_min;
    float output_max;
    float last_error;
    float last_time;
} cm_pid_pd_t;

/**
 * @brief 初始化PD控制器
 * @param kp 比例系数
 * @param kd 微分系数
 * @return 返回新创建的PD控制器指针，失败返回NULL
 */
cm_pid_pd_t* cm_pid_pd_init(float kp, float kd);

/**
 * @brief 设置PD控制器目标值
 * @param pd PD控制器指针
 * @param target 目标值
 */
void cm_pid_pd_set_target(cm_pid_pd_t* pd, float target);

/**
 * @brief 单独设置PD控制器的比例系数
 * @param pd PD控制器指针
 * @param kp 新的比例系数
 */
void cm_pid_pd_set_kp(cm_pid_pd_t* pd, float kp);

/**
 * @brief 单独设置PD控制器的微分系数
 * @param pd PD控制器指针
 * @param kd 新的微分系数
 */
void cm_pid_pd_set_kd(cm_pid_pd_t* pd, float kd);

/**
 * @brief 设置PD控制器输出限幅
 * @param pd PD控制器指针
 * @param min 输出最小值
 * @param max 输出最大值
 */
void cm_pid_pd_set_limit(cm_pid_pd_t* pd, float min, float max);

/**
 * @brief 反初始化PD控制器
 * @param pd 指向PD控制器指针的指针
 * @note 该函数会释放PD控制器内存
 */
void cm_pid_pd_deinit(cm_pid_pd_t**pd);

/**
 * @brief PD控制器计算
 * @param pd PD控制器指针
 * @param input 当前输入值
 * @param time 当前时间
 * @return 返回PD计算输出值
 */
float cm_pid_pd_comput(cm_pid_pd_t* pd, float input, float time);
