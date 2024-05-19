#ifndef _LIDAR_H_
#define _LIDAR_H_

#include "CYdLidar.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;
using namespace ydlidar;

/* comment out 2022.02.21 -----------------------------------------------------
#if defined(_MSC_VER)
#pragma comment(lib, "ydlidar_sdk.lib")
#endif
---------------------------------------------------------------------------- */


void lidar_init(CYdLidar *);


#endif	// _LIDAR_H_


