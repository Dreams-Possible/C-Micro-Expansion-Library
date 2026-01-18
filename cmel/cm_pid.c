//头文件
#include"cm_pid.h"
#include<float.h>

//移植接口
//内存分配接口
#include<stdlib.h>
#define cm_pid_malloc(size) malloc(size)
#define cm_pid_free(p) free(p)
//输入输出接口
#include<stdio.h>
#define cm_pid_log(args,...) printf("[CM_LOG][%s:%d:%s]: " args "\n",__FILE__,__LINE__,__func__,##__VA_ARGS__)

/*以下为位置式PID控制*/

//位置式PID控制器结构体
typedef struct cm_pid_ppid_t
{
    float kp;              // 比例系数
    float ki;              // 积分系数
    float kd;              // 微分系数
    float target;          // 目标值
    float output_min;      // 输出最小值
    float output_max;      // 输出最大值
    float sum_integral;    // 积分项
    float last_error;      // 上一次误差
    float last_time;       // 上一次时间
} cm_pid_ppid_t;

//位置式PID初始化
cm_pid_ppid_t* cm_pid_ppid_init();
//位置式PID设置目标
void cm_pid_ppid_set_target(cm_pid_ppid_t* pid, float target);
//位置式PID设置KP
void cm_pid_ppid_set_kp(cm_pid_ppid_t* pid, float kp);
//位置式PID设置KI
void cm_pid_ppid_set_ki(cm_pid_ppid_t* pid, float ki);
//位置式PID设置KD
void cm_pid_ppid_set_kd(cm_pid_ppid_t* pid, float kd);
//设置输出限幅
void cm_pid_ppid_set_limit(cm_pid_ppid_t* pid, float min, float max);
//位置式PID反初始化
void cm_pid_ppid_deinit(cm_pid_ppid_t**pid);
//位置式PID计算
float cm_pid_ppid_comput(cm_pid_ppid_t* pid, float input, float time);

//位置式PID初始化
cm_pid_ppid_t* cm_pid_ppid_init()
{
    cm_pid_ppid_t* pid = (cm_pid_ppid_t*)cm_pid_malloc(sizeof(cm_pid_ppid_t));
    if(!pid)
    {
        // cm_pid_log("mem err");
        return NULL;
    }
    pid->kp = 0;
    pid->ki = 0;
    pid->kd = 0;
    pid->target = 0;
    pid->output_min = -FLT_MAX;
    pid->output_max = FLT_MAX;
    pid->sum_integral = 0;
    pid->last_error = 0;
    pid->last_time = 0;
    return pid; 
}

//位置式PID设置目标
void cm_pid_ppid_set_target(cm_pid_ppid_t* pid, float target)
{
    pid->target = target;
}

//单独设置位置式PID控制器的比例系数
void cm_pid_ppid_set_kp(cm_pid_ppid_t* pid, float kp)
{
    if(pid)
    {
        pid->kp = kp;
    }
}

//单独设置位置式PID控制器的积分系数
void cm_pid_ppid_set_ki(cm_pid_ppid_t* pid, float ki)
{
    if(pid)
    {
        pid->ki = ki;
    }
}

//单独设置位置式PID控制器的微分系数
void cm_pid_ppid_set_kd(cm_pid_ppid_t* pid, float kd)
{
    if(pid)
    {
        pid->kd = kd;
    }
}

//位置式PID设置输出限幅
void cm_pid_ppid_set_limit(cm_pid_ppid_t* pid, float min, float max)
{
    pid->output_min = min;
    pid->output_max = max;
}

//位置式PID重置
void cm_pid_ppid_reset(cm_pid_ppid_t* pid)
{
    pid->sum_integral = 0;
    pid->last_error = 0;
    pid->last_time = 0;
}

//位置式PID反初始化
void cm_pid_ppid_deinit(cm_pid_ppid_t**pid)
{
    if(*pid)
    {
        cm_pid_free(*pid);
        *pid = NULL;
    }
}

//位置式PID计算
float cm_pid_ppid_comput(cm_pid_ppid_t* pid, float input, float time)
{
    if(time == 0)
    {
        return 0;
    }
    //计算误差
    float error = pid->target - input;
    //计算时间差
    float dt = 0;
    if (pid->last_time > 0)
    {
        dt = time - pid->last_time;
    }
    //比例项
    float proportional = pid->kp * error;
    // cm_pid_log("proportional: kp=%.2f, err=%.2f, prop=%.2f", pid->kp, error, proportional);
    //积分项
    if (dt > 0)
    {
        pid->sum_integral += error * dt;
    }
    float sum_integral = pid->ki * pid->sum_integral;
    // cm_pid_log("integral: ki=%.2f, sum_int=%.2f, integ=%.2f", pid->ki, pid->sum_integral, sum_integral);
    //微分项
    float derivative = 0;
    if (dt > 0)
    {
        derivative = pid->kd * (error - pid->last_error) / dt;
    }
    // cm_pid_log("derivative: kd=%.2f, d_err=%.2f, deriv=%.2f", pid->kd, (error - pid->last_error), derivative);
    //计算输出
    float output = proportional + sum_integral + derivative;
    //输出限幅
    if (output > pid->output_max)
    {
        output = pid->output_max;
    }
    if (output < pid->output_min)
    {
        output = pid->output_min;
    }
    //更新状态
    pid->last_error = error;
    pid->last_time = time;
    // cm_pid_log("pid comput: in=%.2f, err=%.2f, out=%.2f", input, error, output);
    return output;
}

//位置式PD控制器结构体
typedef struct cm_pid_ppd_t
{
    float kp;              // 比例系数
    float kd;              // 微分系数
    float target;          // 目标值
    float output_min;      // 输出最小值
    float output_max;      // 输出最大值
    float last_error;      // 上一次误差
    float last_time;       // 上一次时间
} cm_pid_ppd_t;

//位置式PD初始化
cm_pid_ppd_t* cm_pid_ppd_init();
//位置式PD设置目标
void cm_pid_ppd_set_target(cm_pid_ppd_t* pd, float target);
//位置式PD设置KP
void cm_pid_ppd_set_kp(cm_pid_ppd_t* pd, float kp);
//位置式PD设置KD
void cm_pid_ppd_set_kd(cm_pid_ppd_t* pd, float kd);
//设置输出限幅
void cm_pid_ppd_set_limit(cm_pid_ppd_t* pd, float min, float max);
//位置式PD反初始化
void cm_pid_ppd_deinit(cm_pid_ppd_t**pd);
//位置式PD计算
float cm_pid_ppd_comput(cm_pid_ppd_t* pd, float input, float time);

//位置式PD初始化
cm_pid_ppd_t* cm_pid_ppd_init()
{
    cm_pid_ppd_t* pd = (cm_pid_ppd_t*)cm_pid_malloc(sizeof(cm_pid_ppd_t));
    if(!pd)
    {
        // cm_pid_log("mem err");
        return NULL;
    }
    pd->kp = 0;
    pd->kd = 0;
    pd->target = 0;
    pd->output_min = -FLT_MAX;
    pd->output_max = FLT_MAX;
    pd->last_error = 0;
    pd->last_time = 0;
    return pd; 
}

//位置式PD设置目标
void cm_pid_ppd_set_target(cm_pid_ppd_t* pd, float target)
{
    pd->target = target;
}

//单独设置位置式PD控制器的比例系数
void cm_pid_ppd_set_kp(cm_pid_ppd_t* pd, float kp)
{
    if(pd)
    {
        pd->kp = kp;
    }
}

//单独设置位置式PD控制器的微分系数
void cm_pid_ppd_set_kd(cm_pid_ppd_t* pd, float kd)
{
    if(pd)
    {
        pd->kd = kd;
    }
}

//位置式PD设置输出限幅
void cm_pid_ppd_set_limit(cm_pid_ppd_t* pd, float min, float max)
{
    pd->output_min = min;
    pd->output_max = max;
}

//位置式PD重置
void cm_pid_ppd_reset(cm_pid_ppd_t* pd)
{
    pd->last_error = 0;
    pd->last_time = 0;
}

//位置式PD反初始化
void cm_pid_ppd_deinit(cm_pid_ppd_t**pd)
{
    if(*pd)
    {
        cm_pid_free(*pd);
        *pd = NULL;
    }
}

//位置式PD计算
float cm_pid_ppd_comput(cm_pid_ppd_t* pd, float input, float time)
{
    if(time == 0)
    {
        return 0;
    }
    //计算误差
    float error = pd->target - input;
    //计算时间差
    float dt = 0;
    if (pd->last_time > 0)
    {
        dt = time - pd->last_time;
    }
    //比例项
    float proportional = pd->kp * error;
    // cm_pid_log("proportional: kp=%.2f, err=%.2f, prop=%.2f", pd->kp, error, proportional);
    //微分项
    float derivative = 0;
    if (dt > 0)
    {
        derivative = pd->kd * (error - pd->last_error) / dt;
    }
    // cm_pid_log("derivative: kd=%.2f, d_err=%.2f, deriv=%.2f", pd->kd, (error - pd->last_error), derivative);
    //计算输出
    float output = proportional + derivative;
    //输出限幅
    if (output > pd->output_max)
    {
        output = pd->output_max;
    }
    if (output < pd->output_min)
    {
        output = pd->output_min;
    }
    //更新状态
    pd->last_error = error;
    pd->last_time = time;
    // cm_pid_log("pd comput: in=%.2f, err=%.2f, out=%.2f", input, error, output);
    return output;
}

/*以下为增量式PID控制*/

//增量式PID控制器结构体
typedef struct cm_pid_ipid_t
{
    float kp;              // 比例系数
    float ki;              // 积分系数
    float kd;              // 微分系数
    float target;          // 目标值
    float output_min;      // 输出最小值
    float output_max;      // 输出最大值
    float last_error;      // 上一次误差
    float llast_error;      // 上上一次误差
    // float last_output;     // 上一次输出
    float last_time;       // 上一次时间
} cm_pid_ipid_t;

//增量式PID初始化
cm_pid_ipid_t* cm_pid_ipid_init();
//增量式PID设置目标
void cm_pid_ipid_set_target(cm_pid_ipid_t* pid, float target);
//增量式PID设置KP
void cm_pid_ipid_set_kp(cm_pid_ipid_t* pid, float kp);
//增量式PID设置KI
void cm_pid_ipid_set_ki(cm_pid_ipid_t* pid, float ki);
//增量式PID设置KD
void cm_pid_ipid_set_kd(cm_pid_ipid_t* pid, float kd);
// //增量式PID设置上次输出
// void cm_pid_ipid_set_output(cm_pid_ipid_t* pid, float output);
//设置输出限幅
void cm_pid_ipid_set_limit(cm_pid_ipid_t* pid, float min, float max);
//增量式PID反初始化
void cm_pid_ipid_deinit(cm_pid_ipid_t**pid);
//增量式PID计算
float cm_pid_ipid_comput(cm_pid_ipid_t* pid, float input, float time);

//增量式PID初始化
cm_pid_ipid_t* cm_pid_ipid_init()
{
    cm_pid_ipid_t* pid = (cm_pid_ipid_t*)cm_pid_malloc(sizeof(cm_pid_ipid_t));
    if(!pid)
    {
        // cm_pid_log("mem err");
        return NULL;
    }
    pid->kp = 0;
    pid->ki = 0;
    pid->kd = 0;
    pid->target = 0;
    pid->output_min = -FLT_MAX;
    pid->output_max = FLT_MAX;
    pid->last_error = 0;
    pid->llast_error = 0;
    // pid->last_output = 0;
    pid->last_time = 0;
    return pid; 
}

//增量式PID设置目标
void cm_pid_ipid_set_target(cm_pid_ipid_t* pid, float target)
{
    pid->target = target;
}

//单独设置增量式PID控制器的比例系数
void cm_pid_ipid_set_kp(cm_pid_ipid_t* pid, float kp)
{
    if(pid)
    {
        pid->kp = kp;
    }
}

//单独设置增量式PID控制器的积分系数
void cm_pid_ipid_set_ki(cm_pid_ipid_t* pid, float ki)
{
    if(pid)
    {
        pid->ki = ki;
    }
}

//单独设置增量式PID控制器的微分系数
void cm_pid_ipid_set_kd(cm_pid_ipid_t* pid, float kd)
{
    if(pid)
    {
        pid->kd = kd;
    }
}

// //增量式PID设置上次输出
// void cm_pid_ipid_set_output(cm_pid_ipid_t* pid, float output)
// {
//     pid->last_output = output;
// }

//增量式PID设置输出限幅
void cm_pid_ipid_set_limit(cm_pid_ipid_t* pid, float min, float max)
{
    pid->output_min = min;
    pid->output_max = max;
}

//增量式PID重置
void cm_pid_ipid_reset(cm_pid_ipid_t* pid)
{
    pid->last_error = 0;
    pid->llast_error = 0;
    pid->last_time = 0;
}

//增量式PID反初始化
void cm_pid_ipid_deinit(cm_pid_ipid_t**pid)
{
    if(*pid)
    {
        cm_pid_free(*pid);
        *pid = NULL;
    }
}

//增量式PID计算
float cm_pid_ipid_comput(cm_pid_ipid_t* pid, float input, float time)
{
    if(time == 0)
    {
        return 0;
    }
    // 计算误差
    float error = pid->target - input;
    // 计算时间差
    float dt = 0;
    if (pid->last_time > 0)
    {
        dt = time - pid->last_time;
    }
    // 比例项
    float proportional = pid->kp * (error - pid->last_error);
    // 积分项
    float integral = 0;
    if (dt > 0)
    {
        integral = pid->ki * (error * dt);
    }
    // 微分项
    float derivative = 0;
    if (dt > 0)
    {
        derivative = pid->kd * (error - 2*pid->last_error + pid->llast_error) / dt;
    }
    // 计算增量输出
    float output = proportional + integral + derivative;
    // 输出限幅
    if (output > pid->output_max)
    {
        output = pid->output_max;
    }
    if (output < pid->output_min)
    {
        output = pid->output_min;
    }
    // 更新状态
    pid->llast_error = pid->last_error;
    pid->last_error = error;
    pid->last_time = time;
    // pid->last_output = output;
    return output;
}

//增量式PI控制器结构体
typedef struct cm_pid_ipi_t
{
    float kp;              // 比例系数
    float ki;              // 积分系数
    float kd;              // 微分系数
    float target;          // 目标值
    float output_min;      // 输出最小值
    float output_max;      // 输出最大值
    float last_error;      // 上一次误差
    // float last_output;     // 上一次输出
    float last_time;       // 上一次时间
} cm_pid_ipi_t;

//增量式PI初始化
cm_pid_ipi_t* cm_pid_ipi_init();
//增量式PI设置目标
void cm_pid_ipi_set_target(cm_pid_ipi_t* pid, float target);
//增量式PI设置KP
void cm_pid_ipi_set_kp(cm_pid_ipi_t* pid, float kp);
//增量式PI设置KI
void cm_pid_ipi_set_ki(cm_pid_ipi_t* pid, float ki);
//增量式PI设置KD
void cm_pid_ipi_set_kd(cm_pid_ipi_t* pid, float kd);
// //增量式PI设置上次输出
// void cm_pid_ipi_set_output(cm_pid_ipi_t* pid, float output);
//设置输出限幅
void cm_pid_ipi_set_limit(cm_pid_ipi_t* pid, float min, float max);
//增量式PI反初始化
void cm_pid_ipi_deinit(cm_pid_ipi_t**pid);
//增量式PI计算
float cm_pid_ipi_comput(cm_pid_ipi_t* pid, float input, float time);

//增量式PI初始化
cm_pid_ipi_t* cm_pid_ipi_init()
{
    cm_pid_ipi_t* pid = (cm_pid_ipi_t*)cm_pid_malloc(sizeof(cm_pid_ipi_t));
    if(!pid)
    {
        // cm_pid_log("mem err");
        return NULL;
    }
    pid->kp = 0;
    pid->ki = 0;
    pid->kd = 0;
    pid->target = 0;
    pid->output_min = -FLT_MAX;
    pid->output_max = FLT_MAX;
    pid->last_error = 0;
    // pid->last_output = 0;
    pid->last_time = 0;
    return pid; 
}

//增量式PI设置目标
void cm_pid_ipi_set_target(cm_pid_ipi_t* pid, float target)
{
    pid->target = target;
}

//单独设置增量式PI控制器的比例系数
void cm_pid_ipi_set_kp(cm_pid_ipi_t* pid, float kp)
{
    if(pid)
    {
        pid->kp = kp;
    }
}

//单独设置增量式PI控制器的积分系数
void cm_pid_ipi_set_ki(cm_pid_ipi_t* pid, float ki)
{
    if(pid)
    {
        pid->ki = ki;
    }
}

//单独设置增量式PI控制器的微分系数
void cm_pid_ipi_set_kd(cm_pid_ipi_t* pid, float kd)
{
    if(pid)
    {
        pid->kd = kd;
    }
}

// //增量式PI设置上次输出
// void cm_pid_ipi_set_output(cm_pid_ipi_t* pid, float output)
// {
//     pid->last_output = output;
// }

//增量式PI设置输出限幅
void cm_pid_ipi_set_limit(cm_pid_ipi_t* pid, float min, float max)
{
    pid->output_min = min;
    pid->output_max = max;
}

//增量式PI重置
void cm_pid_ipi_reset(cm_pid_ipi_t* pid)
{
    pid->last_error = 0;
    pid->last_time = 0;
}

//增量式PI反初始化
void cm_pid_ipi_deinit(cm_pid_ipi_t**pid)
{
    if(*pid)
    {
        cm_pid_free(*pid);
        *pid = NULL;
    }
}

//增量式PI计算
float cm_pid_ipi_comput(cm_pid_ipi_t* pid, float input, float time)
{
    if(time == 0)
    {
        return 0;
    }
    // 计算误差
    float error = pid->target - input;
    // 计算时间差
    float dt = 0;
    if (pid->last_time > 0)
    {
        dt = time - pid->last_time;
    }
    // 比例项
    float proportional = pid->kp * (error - pid->last_error);
    // 积分项
    float integral = 0;
    if (dt > 0)
    {
        integral = pid->ki * (error * dt);
    }
    // 计算增量输出
    float output = proportional + integral;
    // 输出限幅
    if (output > pid->output_max)
    {
        output = pid->output_max;
    }
    if (output < pid->output_min)
    {
        output = pid->output_min;
    }
    // 更新状态
    // pid->llast_error = pid->last_error;
    pid->last_error = error;
    pid->last_time = time;
    // pid->last_output = output;
    return output;
}
