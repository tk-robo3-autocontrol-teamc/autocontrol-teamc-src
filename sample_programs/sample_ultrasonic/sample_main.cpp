#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wiringPi.h>

int main(int argc, char **argv)
{
    int level;

    if (wiringPiSetupGpio() == -1) {
        printf("wiringPiSetupGpio() error\n");
        return -1;
    }

    pinMode(14, OUTPUT);
    pinMode(4, INPUT);

    digitalWrite(14, LOW);
    delayMicroseconds(2);

    digitalWrite(14, HIGH);
    delayMicroseconds(10);

    level = digitalRead(4);
    printf("level=%d\n", level);

    return 0;
}