#include "math_util.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <bitset>

#include <CGAL/Cartesian.h>

double
angle_with_x_axis(CGAL::Point_2<CGAL::Cartesian<double>> p, CGAL::Point_2<CGAL::Cartesian<double>> q)
{
  return atan2((q.y() - p.y()), (q.x() - p.x())) * 180 / M_PI;
}

bool
is_inside_circle(CGAL::Point_2<CGAL::Cartesian<double>> circle_origin,
                  double radius,
                  CGAL::Point_2<CGAL::Cartesian<double>> p)
{
  return (pow(p.x() - circle_origin.x(), 2) + pow(p.y() - circle_origin.y(), 2) < pow(radius, 2));
}

angle_range
angle_range_intersection(angle_range a1, angle_range a2)
{
  double mid_a1 = (a1.start + a1.end) / 2;
  double mid_a2 = (a2.start + a2.end) / 2;
  double diff_a1 = (a1.end - a1.start) / 2;
  double diff_a2 = (a2.end - a2.start) / 2;

  double c_diff_a1 = cos(diff_a1 * M_PI / 180.0);
  double c_diff_a2 = cos(diff_a2 * M_PI / 180.0);

  bool a2_start_inside_a1 = (cos((mid_a1 - a2.start) * M_PI / 180.0) >= c_diff_a1);
  bool a2_end_inside_a1 = (cos((mid_a1 - a2.end) * M_PI / 180.0) >= c_diff_a1);
  bool a1_start_inside_a2 = (cos((mid_a2 - a1.start) * M_PI / 180.0) >= c_diff_a2);
  bool a1_end_inside_a2 = (cos((mid_a2 - a1.end) * M_PI / 180.0) >= c_diff_a2);

  int8_t angle_info = 0;
  if(a2_start_inside_a1)
  {
    angle_info = angle_info | (1 << 3);
  }
  if(a2_end_inside_a1)
  {
    angle_info = angle_info | (1 << 2);
  }
  if(a1_start_inside_a2)
  {
    angle_info = angle_info | (1 << 1);
  }
  if(a1_end_inside_a2)
  {
    angle_info = angle_info | (1);
  }

  angle_range intersection_angle;
  switch(angle_info)
  {
    case 0: // binary representation 0000
    {
      intersection_angle = {0, 0};
      break;
    }
    case 15: // binary representation 1111
    {
      intersection_angle = a1; // or a2
      break;
    }
    case 3: // binary representation 0011
    {
      intersection_angle = {a1.start, a1.end};
      break;
    }
    case 9: // binary representation 1001
    {
      intersection_angle = {a2.start, a1.end};
      break;
    }
    case 6: // binary representation 0110
    {
      intersection_angle = {a1.start, a2.end};
      break;
    }
    case 12: // binary representation 1100
    {
      intersection_angle = {a2.start, a2.end};
      break;
    }
    case 7: // binary representation 0111
    {
      intersection_angle = {a1.start, a1.end};
      break;
    }
    case 11: // binary representation 1011
    {
      intersection_angle = {a1.start, a1.end};
      break;
    }
    case 14: // binary representation 1110
    {
      intersection_angle = {a2.start, a2.end};
      break;
    }
    case 13: // binary representation 1101
    {
      intersection_angle = {a2.start, a2.end};
      break;
    }
  }

  //std::cout << std::bitset<4>(angle_info) << std::endl;

  return intersection_angle;
}

std::array<CGAL::Point_2<CGAL::Cartesian<double>>, 2>
get_tangent_points(CGAL::Point_2<CGAL::Cartesian<double>> circle_origin,
                    double radius,
                    CGAL::Point_2<CGAL::Cartesian<double>> p)
{
  std::array<CGAL::Point_2<CGAL::Cartesian<double>>, 2> tangent_points;

  double dist_to_origin = sqrt(pow((p.x() - circle_origin.x()), 2) + pow((p.y() - circle_origin.y()), 2));
  double th = acos(radius / dist_to_origin);
  double d = atan2((p.y() - circle_origin.y()), (p.x() - circle_origin.x()));
  double d1 = d + th;
  double d2 = d - th;
  CGAL::Point_2<CGAL::Cartesian<double>> ta(circle_origin.x() + radius * cos(d1), circle_origin.y() + radius * sin(d1)),
                                          tb(circle_origin.x() + radius * cos(d2), circle_origin.y() + radius * sin(d2));
  tangent_points = {ta, tb};
  return tangent_points;
}
