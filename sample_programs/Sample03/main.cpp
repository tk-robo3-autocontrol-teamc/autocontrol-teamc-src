#include <iostream>
#include "car.h"

using namespace std;

int main(int argc, char **argv)
{
    Car car;
    car.speed = 40;
    car.drive(1.5);

    return 0;
}