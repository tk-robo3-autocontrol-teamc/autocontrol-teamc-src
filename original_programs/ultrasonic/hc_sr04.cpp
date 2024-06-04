#include "hc_sr04.h"
#include <chrono>

HCSR04::HCSR04(int trig_pin, int echo_pin)
{
    if (wiringPiSetupGpio() == -1) {
        printf("wiringPiSetupGpio() error\n");
        return;
    }
    this->trig_bcm_pin = trig_pin;
    this->echo_bcm_pin = echo_pin;
    pinMode(this->trig_bcm_pin, OUTPUT);
    pinMode(this->echo_bcm_pin, INPUT);
}

double HCSR04::getEchoTime()
{
    std::chrono::system_clock::time_point echo_off, echo_on;
    double echo_time = 0;

    digitalWrite(this->trig_bcm_pin, LOW);
    usleep(1000);
    digitalWrite(this->trig_bcm_pin, HIGH);
    usleep(10);
    digitalWrite(this->trig_bcm_pin, LOW);

    while (digitalRead(this->echo_bcm_pin) == LOW);
    echo_off = std::chrono::system_clock::now();

    while (digitalRead(this->echo_bcm_pin) == HIGH);
    echo_on = std::chrono::system_clock::now();
    
    echo_time = std::chrono::duration_cast<std::chrono::microseconds>(echo_on-echo_off).count();
    return echo_time;
}

double HCSR04::getDistancce(double temp)
{
    double echo_time = 0, distance = 0;
    echo_time = this->getEchoTime();
    echo_time /= 1000000;
    printf("echo_time : %fus\n", echo_time);
    distance = (331.50 + 0.606681 * temp) * echo_time / 2.0;
    return distance;
}
