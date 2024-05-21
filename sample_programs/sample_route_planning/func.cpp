#include <iostream>
#include "func.h"

// 障害物を2個同時に検知した場合のポテンシャル関数計算
double PthPln::calc_pot(double x, double y)
{
    double obst_pot[OBST];

    obst_pot[0] = 1.0 / sqrt((x - obst_x[0])*(x - obst_x[0]) + (y - obst_y[0])*(y - obst_y[0]));
    obst_pot[1] = 1.0 / sqrt((x - obst_x[1])*(x - obst_x[1]) + (y - obst_y[1])*(y - obst_y[1]));
    double Goal_pot = -1.0 / sqrt((x - Goal_x)*(x - Goal_x) + (y - Goal_y)*(y - Goal_y));

    double pot = obst_pot[0] * Weight_obst[0] + obst_pot[1] * Weight_obst[1] + Goal_pot * Wright_Goal;

    return pot;
}