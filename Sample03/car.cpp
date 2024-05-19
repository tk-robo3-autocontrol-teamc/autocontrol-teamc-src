#include <iostream>
#include "car.h"

using namespace std;

void Car::drive(double hour)
{
    cout << "I drove a car at " << speed << " km/h " << "for " << hour << " hours" << endl;
    cout << "I moved " << speed*hour << " km" << endl;
}