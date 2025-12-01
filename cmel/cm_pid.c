//头文件
#include"cm_pid.h"
#include<float.h>

//移植接口
//内存分配接口
#include<stdlib.h>
#define pid_malloc(size) malloc(size)
#define pid_free(p) free(p)
//输入输出接口
#include<stdio.h>
#define pid_log(args,...) printf("[CM_LOG][%s:%d:%s]: " args "\n",__FILE__,__LINE__,__func__,##__VA_ARGS__)

//PID初始化
cm_pid_pid_t* cm_pid_pid_init(float kp, float ki, float kd);
//PID设置目标
void cm_pid_pid_set_target(cm_pid_pid_t* pid, float target);
//PID设置KP
void cm_pid_pid_set_kp(cm_pid_pid_t* pid, float kp);
//PID设置KI
void cm_pid_pid_set_ki(cm_pid_pid_t* pid, float ki);
//PID设置KD
void cm_pid_pid_set_kd(cm_pid_pid_t* pid, float kd);
//设置输出限幅
void cm_pid_pid_set_limit(cm_pid_pid_t* pid, float min, float max);
//PID反初始化
void cm_pid_pid_deinit(cm_pid_pid_t**pid);
//PID计算
float cm_pid_pid_comput(cm_pid_pid_t* pid, float input, float time);

//PID初始化
cm_pid_pid_t* cm_pid_pid_init(float kp, float ki, float kd)
{
    cm_pid_pid_t* pid = (cm_pid_pid_t*)pid_malloc(sizeof(cm_pid_pid_t));
    if(!pid)
    {
        pid_log("mem err");
        return NULL;
    }
    pid->kp = kp;
    pid->ki = ki;
    pid->kd = kd;
    pid->target = 0;
    pid->output_min = -FLT_MAX;
    pid->output_max = FLT_MAX;
    pid->sum_integral = 0;
    pid->last_error = 0;
    pid->last_time = 0;
    return pid; 
}

//PID设置目标
void cm_pid_pid_set_target(cm_pid_pid_t* pid, float target)
{
    pid->target = target;
}

//单独设置PID控制器的比例系数
void cm_pid_pid_set_kp(cm_pid_pid_t* pid, float kp)
{
    if(pid)
    {
        pid->kp = kp;
    }
}

//单独设置PID控制器的积分系数
void cm_pid_pid_set_ki(cm_pid_pid_t* pid, float ki)
{
    if(pid)
    {
        pid->ki = ki;
    }
}

//单独设置PID控制器的微分系数
void cm_pid_pid_set_kd(cm_pid_pid_t* pid, float kd)
{
    if(pid)
    {
        pid->kd = kd;
    }
}

//PID设置输出限幅
void cm_pid_pid_set_limit(cm_pid_pid_t* pid, float min, float max)
{
    pid->output_min = min;
    pid->output_max = max;
}

//PID重置
void cm_pid_pid_reset(cm_pid_pid_t* pid)
{
    pid->sum_integral = 0;
    pid->last_error = 0;
    pid->last_time = 0;
}

//PID反初始化
void cm_pid_pid_deinit(cm_pid_pid_t**pid)
{
    if(*pid)
    {
        pid_free(*pid);
        *pid = NULL;
    }
}

//PID计算
float cm_pid_pid_comput(cm_pid_pid_t* pid, float input, float time)
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
    // pid_log("proportional: kp=%.2f, err=%.2f, prop=%.2f", pid->kp, error, proportional);
    //积分项
    if (dt > 0)
    {
        pid->sum_integral += error * dt;
    }
    float sum_integral = pid->ki * pid->sum_integral;
    // pid_log("integral: ki=%.2f, sum_int=%.2f, integ=%.2f", pid->ki, pid->sum_integral, sum_integral);
    //微分项
    float derivative = 0;
    if (dt > 0)
    {
        derivative = pid->kd * (error - pid->last_error) / dt;
    }
    // pid_log("derivative: kd=%.2f, d_err=%.2f, deriv=%.2f", pid->kd, (error - pid->last_error), derivative);
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
    // pid_log("pid comput: in=%.2f, err=%.2f, out=%.2f", input, error, output);
    return output;
}

//PD初始化
cm_pid_pd_t* cm_pid_pd_init(float kp, float kd);
//PD设置目标
void cm_pid_pd_set_target(cm_pid_pd_t* pd, float target);
//PD设置KP
void cm_pid_pd_set_kp(cm_pid_pd_t* pd, float kp);
//PD设置KD
void cm_pid_pd_set_kd(cm_pid_pd_t* pd, float kd);
//设置输出限幅
void cm_pid_pd_set_limit(cm_pid_pd_t* pd, float min, float max);
//PD反初始化
void cm_pid_pd_deinit(cm_pid_pd_t**pd);
//PD计算
float cm_pid_pd_comput(cm_pid_pd_t* pd, float input, float time);

//PD初始化
cm_pid_pd_t* cm_pid_pd_init(float kp, float kd)
{
    cm_pid_pd_t* pd = (cm_pid_pd_t*)pid_malloc(sizeof(cm_pid_pd_t));
    if(!pd)
    {
        pid_log("mem err");
        return NULL;
    }
    pd->kp = kp;
    pd->kd = kd;
    pd->target = 0;
    pd->output_min = -FLT_MAX;
    pd->output_max = FLT_MAX;
    pd->last_error = 0;
    pd->last_time = 0;
    return pd; 
}

//PD设置目标
void cm_pid_pd_set_target(cm_pid_pd_t* pd, float target)
{
    pd->target = target;
}

//单独设置PD控制器的比例系数
void cm_pid_pd_set_kp(cm_pid_pd_t* pd, float kp)
{
    if(pd)
    {
        pd->kp = kp;
    }
}

//单独设置PD控制器的微分系数
void cm_pid_pd_set_kd(cm_pid_pd_t* pd, float kd)
{
    if(pd)
    {
        pd->kd = kd;
    }
}

//PD设置输出限幅
void cm_pid_pd_set_limit(cm_pid_pd_t* pd, float min, float max)
{
    pd->output_min = min;
    pd->output_max = max;
}

//PD重置
void cm_pid_pd_reset(cm_pid_pd_t* pd)
{
    pd->last_error = 0;
    pd->last_time = 0;
}

//PD反初始化
void cm_pid_pd_deinit(cm_pid_pd_t**pd)
{
    if(*pd)
    {
        pid_free(*pd);
        *pd = NULL;
    }
}

//PD计算
float cm_pid_pd_comput(cm_pid_pd_t* pd, float input, float time)
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
    // pid_log("proportional: kp=%.2f, err=%.2f, prop=%.2f", pd->kp, error, proportional);
    //微分项
    float derivative = 0;
    if (dt > 0)
    {
        derivative = pd->kd * (error - pd->last_error) / dt;
    }
    // pid_log("derivative: kd=%.2f, d_err=%.2f, deriv=%.2f", pd->kd, (error - pd->last_error), derivative);
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
    // pid_log("pd comput: in=%.2f, err=%.2f, out=%.2f", input, error, output);
    return output;
}
