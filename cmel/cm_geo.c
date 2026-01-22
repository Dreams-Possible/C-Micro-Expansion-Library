#include"cm_geo.h"
// #include<string.h>
#include <math.h>
#include <float.h>

//移植接口
//内存分配接口
#include<stdlib.h>
#define cli_malloc(size) malloc(size)
#define cli_free(p) free(p)
//输入输出接口
#include<stdio.h>
#define cli_log(args,...) printf("[CM_LOG][%s:%d:%s]: " args "\n",__FILE__,__LINE__,__func__,##__VA_ARGS__)

// 计算两点之间的距离
float cm_geo_2dp_dist(cm_geo_2dp_t p1, cm_geo_2dp_t p2);
// 计算两个点之间的斜率
float cm_geo_calcu_slope(cm_geo_2dp_t p1, cm_geo_2dp_t p2);
// 计算三点曲率（包括判断左转还是右转）
float cm_geo_calcu_curva(cm_geo_2dp_t p1, cm_geo_2dp_t p2, cm_geo_2dp_t p3, uint8_t* direction);

// 计算两点之间的距离
float cm_geo_2dp_dist(cm_geo_2dp_t p1, cm_geo_2dp_t p2)
{
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

// 计算两个点之间的斜率
float cm_geo_calcu_slope(cm_geo_2dp_t p1, cm_geo_2dp_t p2)
{
    // 确保 x2 - x1 不为零（避免除零错误）
    if (p2.x - p1.x == 0)
    {
        return FLT_MAX;  // 垂直线的斜率
    }
    return (p2.y - p1.y) / (p2.x - p1.x);
}

// 计算三点曲率（包括判断左转还是右转）
float cm_geo_calcu_curva(cm_geo_2dp_t p1, cm_geo_2dp_t p2, cm_geo_2dp_t p3, uint8_t* direction)
{
    // 计算两条边的长度
    float a = cm_geo_2dp_dist(p2, p3);  // 边 p2-p3
    float b = cm_geo_2dp_dist(p1, p3);  // 边 p1-p3
    float c = cm_geo_2dp_dist(p1, p2);  // 边 p1-p2

    // 叉积（计算三点的有向面积，判断方向）
    float cross_product = (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);

    // 判断转向方向（叉积的符号）
    if (cross_product > 0)
    {
        *direction = -1;  // 左转
    } else
    if (cross_product < 0)
    {
        *direction = 1;  // 右转
    } else
    {
        *direction = 0;  // 共线，无法判断转向
    }

    // 计算三角形的面积
    float area2 = fabs(cross_product);

    // 计算外接圆半径（曲率）
    if (area2 < 1e-6) {
        return 0.0;  // 防止分母为0，表示三点共线或极小面积
    }

    // 外接圆半径 R = (a * b * c) / (4 * Area)
    float curvature_radius = (a * b * c) / (4.0 * area2);
    
    // 曲率：k = 1 / R
    return 1.0 / curvature_radius;
}
