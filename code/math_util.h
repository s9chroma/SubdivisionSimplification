#ifndef MATH_H
#define MATH_H

#include <CGAL/Cartesian.h>

struct angle_range
{
  double start;
  double end;
};

double
angle_with_x_axis(CGAL::Point_2<CGAL::Cartesian<double>> p,
                  CGAL::Point_2<CGAL::Cartesian<double>> q);

bool
is_inside_circle(CGAL::Point_2<CGAL::Cartesian<double>> circle_origin,
                  double radius,
                  CGAL::Point_2<CGAL::Cartesian<double>> p);

angle_range
angle_range_intersection(angle_range a1, angle_range a2);

std::array<CGAL::Point_2<CGAL::Cartesian<double>>, 2>
get_tangent_points(CGAL::Point_2<CGAL::Cartesian<double>> circle_origin,
                    double radius,
                    CGAL::Point_2<CGAL::Cartesian<double>> p);

#endif
