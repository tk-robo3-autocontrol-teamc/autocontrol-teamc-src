#include <iostream>
#include "func.h"

int main(int argc, char **argv)
{
    FILE *fp1 = fopen("potential_1.txt", "w");
    FILE *fp2 = fopen("potential_2.txt", "w");
    FILE *fp3 = fopen("potential_3.txt", "w");
    FILE *gp1, *gp2;
    const char *data_file, *data_file2, *data_file3;

    double delta = 0.5;
    double max = 1.0;
    double alpha = 1.0;
    double xp = 0.0, yp = 0.0;  // 開始座標

    if (fp1 == NULL) {
        printf("Err\n");
        return -1;
    }
    if (fp2 == NULL) {
        printf("Err\n");
        return -1;
    }
    if (fp3 == NULL) {
        printf("Err\n");
        return -1;
    }

    PthPln path;

    // 障害物一の設定
    path.obst_x[0] = 55.0;
    path.obst_y[0] = 2.5;
    path.obst_x[1] = 35.0;
    path.obst_y[1] = -2.5;

    // 目標一の設定
    path.Goal_x = 75.0;
    path.Goal_y = 0.0;

    // 重み係数の設定
    path.Weight_obst[0] = 0.35;
    path.Weight_obst[1] = 0.35;
    path.Wright_Goal = 10.0;

    // ポテンシャル場生成
    for (double x = 0; x < 100; x += delta) {
        for (double y = -50; y < 50; y += delta) {
            double pot = path.calc_pot(x, y);
            if (pot > max) pot = max;
            if (pot < -max) pot = -max;

            fprintf(fp1, "%lf, %lf, %lf\n", x, y, pot);
        }
        fprintf(fp1, "\n");
    }
    fclose(fp1);

    // 勾配ベクトル場の生成
    delta = 1.0;
    for (double x = 0; x < 100; x += delta) {
        for (double y = -50; y < 50; y += delta) {
            double vx = -(path.calc_pot(x + delta, y) - path.calc_pot(x, y))/delta;
            double vy = -(path.calc_pot(x, y + delta) - path.calc_pot(x, y))/delta;

            double v = sqrt(vx*vx + vy*vy);
            vx /= v;
            vy /= v;

            if (!isnan(vx) && !isnan(vy)) {
                fprintf(fp2, "%lf, %lf, %lf, %lf, %lf\n", x, y, vx, vy, v);
            }
        }
    }
    fclose(fp2);

    // 経路探索
    delta = 0.1;
    for (int i = 0; i < 1000; i++) {
            double vx = -(path.calc_pot(xp + delta, yp) - path.calc_pot(xp, yp))/delta;
            double vy = -(path.calc_pot(xp, yp + delta) - path.calc_pot(xp, yp))/delta;

            double v = sqrt(vx*vx + vy*vy);
            vx /= v;
            vy /= v;

            xp += alpha*vx;
            yp += alpha*vy;

            if (path.Goal_x-xp < 0.25 && path.Goal_x-xp > -0.25) {
                break;
            }
            fprintf(fp3, "%lf, %lf\n", xp, yp);
    }
    fclose(fp3);

    // ポテンシャル場の3次元グラフ生成
    data_file = "potential_1.txt";
    gp1 = popen("gnuplot -persist", "w");
    fprintf(gp1, "set pm3d corners2color max\n");
    fprintf(gp1, "set pm3d depthorder\n");
    fprintf(gp1, "set datafile separator \",\"\n");
    fprintf(gp1, "set xrange[0:100]\n");
    fprintf(gp1, "set yrange[-50:50]\n");
    fprintf(gp1, "set xlabel \"X\"\n");
    fprintf(gp1, "set ylabel \"Y\"\n");
    fprintf(gp1, "splot \"%s\" with pm3d notitle\n", data_file);

    // 勾配ベクトル場の生成経路探索
    data_file2 = "potential_2.txt";
    data_file3 = "potential_3.txt";
    gp2 = popen("gnuplot -persist", "w");
    fprintf(gp2, "set datafile separator \",\"\n");
    fprintf(gp2, "set xrange[0:100]\n");
    fprintf(gp2, "set yrange[-50:50]\n");
    fprintf(gp2, "set xlabel \"X [cm]\"\n");
    fprintf(gp2, "set ylabel \"Y [cm]\"\n");
    fprintf(gp2, "set size ratio 1\n");
    fprintf(gp2, "set palette rgb 33,13,10\n");
    fprintf(gp2, "plot \"%s\" using 1:2:3:4:5 with vector lc palette ti \"\", \
                       \"%s\" using 1:2 title \"path\"\n", data_file2, data_file3);
    return 0;
}