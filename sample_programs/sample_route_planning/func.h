#ifndef _FUNC_H_
#define _FUNC_H_

#include <stdio.h>
#include <math.h>

#define OBST    255

class PthPln {
public:
    // 障害物の位置
    double obst_x[OBST];
    double obst_y[OBST];

    // 目標位置
    double Goal_x;
    double Goal_y;

    // 重み係数
    double Weight_obst[OBST];
    double Wright_Goal;

    // ポテンシャル関数計算
    double calc_pot(double x, double y);
};

#endif // _FUNC_H_