#include "geom2d.h"
#include <stdio.h>
#include <math.h>

int main(int argc, char** argv)
{
  if (argc != 7)
  {
  	printf("[ERROR] Usage : ./test_geom2d P.x P.y A.x A.y B.x B.y\n");
  	return -1;
  }

  double x,y;
  sscanf(argv[1], "%lf", &x);
  sscanf(argv[2], "%lf", &y);

  Point P = set_point(x, y);

  sscanf(argv[3], "%lf", &x);
  sscanf(argv[4], "%lf", &y);

  Point A = set_point(x, y);

  sscanf(argv[5], "%lf", &x);
  sscanf(argv[6], "%lf", &y);

  Point B = set_point(x, y);
  
  printf("%f\n",distance_point_segment(P, A, B));
}
