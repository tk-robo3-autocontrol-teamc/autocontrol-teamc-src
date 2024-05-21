#include <time.h>
#include <math.h>
#include <chrono>
#include <iostream>
#include "drv_fnc.h"

#define Kp 10
#define Ki 10
#define Kd 10

int main(int argc, char *argv[])
{
    Drive drive;
    int last_pls_L = 0, last_pls_R = 0, // 時刻1での車輪位置
        crr_pls_L = 0, crr_pls_R = 0,   // 時刻2での車輪位置
        delt_pls_L = 0, delt_pls_R = 0; // 時刻2と時刻1の時間での車輪位置の変化量
    std::chrono::system_clock::time_point time1, time2;
    double dt = 0.0,                    // 車輪位置が変わった時間tでの変化量[s]
           wL, wR,                      // 車輪の角速度
           v, vth,                      // ロボットの速度、角速度
           th = 0, x = 0, y = 0,                    // ロボットの位置・姿勢
           vx, vy,                      // 世界座標系でのロボット速度
           whl_pls                      // 車輪1回転のエンコーダパルス数 : 201469
                   = IENCORDER_COUNT * DGEAR_RATIO * IMULTIPLY
                   * IWHEEL_GEAR / IMOTOR_GEAR,
           r = DWHEEL_DIAMETER / 2 / 1000,  // 車輪の半径                   : 41[mm] = 0.041[m]
           T = DTREAD / 1000,              // トレッド(左右の車輪間の距離)  : 307.6[mm] = 0.3076[m]
           tm, v_des, x_des, y_des, e1, e2, u1_int, u2_int, u1, u2, ul, ur, yA, xT, e2_old;

    while(1) {
        time1 = std::chrono::system_clock::now();           // 時間取得1
        dt = 0.0;

        last_pls_L = crr_pls_L;                             // 車輪位置の取得1
        last_pls_R = crr_pls_R;

        crr_pls_L = drive.GetPositionIs(drive.iNodeIDLeft); // 車輪位置の取得2
        crr_pls_R = drive.GetPositionIs(drive.iNodeIDLeft);

        time2 = std::chrono::system_clock::now();           // 時間取得2
        dt = std::chrono::duration_cast                     // dt = 時間取得2 - 時間取得1
                    <std::chrono::microseconds>(time2-time1).count() / 1000000;

        delt_pls_L = crr_pls_L - last_pls_L;                // todo 時刻2と時刻1の時間での車輪位置の変化量
        delt_pls_R = crr_pls_R - last_pls_R;

        wL = delt_pls_L / whl_pls * 2*M_PI / dt;          // 車輪角速度の計算
        wR = delt_pls_R / whl_pls * 2*M_PI / dt;
        v = r * (wR + wL) / 2;                              // 並列速度vの計算
        vth = r * (wR - wL) / T;                            // ロボットの角速度の計算

        th = vth * dt + th;                                 // ロボットの姿勢θの計算(世界座標)
        vx = v * cos(th);                                   // ロボットのx方向y方向の速度の計算
        vy = v * sin(th);
        x = vx * dt + x;                                    // ロボットの位置の計算(世界座標)
        y = vy * dt + y;
        yA = y - yA;
        xT = x - xT;

        tm += dt;               //経過時間

    /* cos曲線の経路座標計算*/
        v_des = 130*(1-exp(-5*tm));         
        x_des = v_des * tm;
        y_des = yA/2.0 * (1 - cos((2*3.14*x_des) / xT));

        e1 = v_des - v;     // [mm/s]
        e2 = y_des - y;     // [mm]

    /* PID制御器の積分項の計算　*/
        u1_int = Ki * e1;   
        u2_int = Ki * e2;

        u1 = Kp * e1 + u1_int;
        u2 = Kp * e2 + Kd * (e2_old - e2)/dt;

        e2_old = e2;

        ul = u1 - T/2 * u2;
        ur = u1 + T/2 * u2;

        break;
    }

    return 0;
}