#include "hc_sr04.h"

#define HCSR04_TRIG_BCM_PIN 14
#define HCSR04_ECHO_BCM_PIN 4

int main(void)
{
    HCSR04 hcsr04_instance = HCSR04(HCSR04_TRIG_BCM_PIN, HCSR04_ECHO_BCM_PIN);
    double distance;
    int temp;

    while (true) {
        temp = 26.4;
        distance = hcsr04_instance.getDistancce(temp);
        printf("distance  : %fcm\n", distance * 100);
        sleep(1);
    }

    return 0;
}
