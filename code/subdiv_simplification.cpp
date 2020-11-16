#include "subdiv_simplification.h"
#include "math_util.h"

#define _USE_MATH_DEFINES
#include <math.h>

std::vector<shortcut>
compute_allowed_shortcuts(std::vector<CGAL::Point_2<CGAL::Cartesian<double>>> polygonal_chain,
                          double error)
{
  std::vector<shortcut> accepted_shortcuts;
  for(int i = 0; i < polygonal_chain.size() - 1; i++)
  {
    shortcut best_for_i;
    angle_range I = {-180.0, 180.0};
    int j = i + 1;
    while((I.start <= I.end) && (j < polygonal_chain.size()))
    {
      //printf("i: %d, j: %d, I: {%f, %f}\t", i, j, I.start, I.end);
      double angle = angle_with_x_axis(polygonal_chain.at(i), polygonal_chain.at(j));
      //printf("Angle: %f\n", angle);
      if((angle >= I.start) && (angle <= I.end))
      {
        best_for_i = {polygonal_chain.at(i), polygonal_chain.at(j)};
      }
      if(is_inside_circle(polygonal_chain.at(j), error, polygonal_chain.at(i)) != true)
      {
        std::array<CGAL::Point_2<CGAL::Cartesian<double>>, 2> points =
              get_tangent_points(polygonal_chain.at(j), error, polygonal_chain.at(i));
        angle_range J = {angle_with_x_axis(polygonal_chain.at(i), std::get<0>(points)),
                          angle_with_x_axis(polygonal_chain.at(i), std::get<1>(points))};
        I = angle_range_intersection(I, J);
        //printf("i: %d, j: %d, Updated I: {%f, %f}\n\n", i, j, I.start, I.end);
      }
      j += 1;
    }
    accepted_shortcuts.push_back(best_for_i);
  }
  return accepted_shortcuts;
}
