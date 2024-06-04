#ifndef _HC_SR04_H_
#define _HC_SR04_H_

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wiringPi.h>

class HCSR04 {
    int trig_bcm_pin;
    int echo_bcm_pin;
public:
    HCSR04(int trig_pin, int echo_pin); 
    double getEchoTime();
    double getDistancce(double temp);
};

#endif // _HC_SR04_H_
