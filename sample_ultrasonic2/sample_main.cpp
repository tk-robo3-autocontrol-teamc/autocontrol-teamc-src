#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <wiringPi.h>

int main(int argc, char **argv)
{
    struct timeval t0, t1;
    double micros;

    while (1) {
        gettimeofday(&t0, NULL);

        delayMicroseconds(10);

        gettimeofday(&t1, NULL);

        micros = (double) ((t1.tv_sec - t0.tv_sec) + (t1.tv_usec - t0.tv_usec) / 1000000.0);
        printf("micros=%f\n", micros);
    }

    return 0;
}