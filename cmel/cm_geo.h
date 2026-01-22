#pragma once

#include<stdint.h>

//  2D点
typedef struct cm_geo_2dp_t{
    double x;
    double y;
} cm_geo_2dp_t;

// 计算两点之间的距离
float cm_geo_2dp_dist(cm_geo_2dp_t p1, cm_geo_2dp_t p2);
// 计算两个点之间的斜率
float cm_geo_calcu_slope(cm_geo_2dp_t p1, cm_geo_2dp_t p2);
// 计算三点曲率（包括判断左转还是右转）
float cm_geo_calcu_curva(cm_geo_2dp_t p1, cm_geo_2dp_t p2, cm_geo_2dp_t p3, uint8_t* direction);
