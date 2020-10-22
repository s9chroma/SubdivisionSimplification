#define _USE_MATH_DEFINES

#include <math.h>
#include "geom.h"
#include <stdio.h>

double
compute_angle(Line2D l1, Line2D l2)
{
  double m1 = ((l1.p2.y - l1.p1.y) / (l1.p2.x - l1.p1.x));
  double m2 = ((l2.p2.y - l2.p1.y) / (l2.p2.x - l2.p1.x));
  return(atan((m1 - m2) / (1 + m1 * m2)));
}

double
radians_to_degrees(double x)
{
  return(x * (180 / M_PI));
}
