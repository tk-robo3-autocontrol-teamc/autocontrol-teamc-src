// 2022.02.21 --> mod 2022.05.05
#include <stdio.h>
#include "lidar.h"


int main(void)
{
  CYdLidar laser;
  LaserScan scan;


  lidar_init(&laser);

  if (laser.doProcessSimple(scan)) {
    fprintf(stdout, "Scan received[%lu]: %u ranges is [%f]Hz\n",
    scan.stamp,
    (unsigned int)scan.points.size(), 1.0 / scan.config.scan_time);
    fflush(stdout);
  } else {
    fprintf(stderr, "Failed to get Lidar Data\n");
    fflush(stderr);
  }

  
  for(int i=0; i<scan.points.size(); i++){
    printf("%f\t%f\n", scan.points[i].angle, scan.points[i].range);
  }


  laser.turnOff();
  laser.disconnecting();

  return 0;	
}


