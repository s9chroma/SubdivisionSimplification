#include "subdiv_simplification.h"
#include "math_util.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include <CGAL/intersections.h>

tangent_type
get_tangent_type(line l, CGAL::Point_2<CGAL::Cartesian<double>> p1,
    CGAL::Point_2<CGAL::Cartesian<double>> p2)
{
  double cross_product_1 = ((l.end.x() - l.start.x()) * (l.end.y() - p1.y())) -
      ((l.end.y() - l.start.y()) * (l.end.x() - p1.x()));
  double cross_product_2 = ((l.end.x() - l.start.x()) * (l.end.y() - p2.y())) -
      ((l.end.y() - l.start.y()) * (l.end.x() - p2.x()));

  //printf("%f is cp_1, %f is cp_2\n", cross_product_1, cross_product_2);

  if(cross_product_1 > 0 && cross_product_2 > 0)
  {
    return tangent_type::maximal;
  }
  else if(cross_product_1 < 0 && cross_product_2 < 0)
  {
    return tangent_type::minimal;
  }
  else if(cross_product_1 == 0 && cross_product_2 == 0)
  {
    if(l.end.y() > p1.y())
    {
      return tangent_type::maximal;
    }
    else
    {
      return tangent_type::minimal;
    }
  }
  return tangent_type::neither;
}

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

std::vector<tangent_splitter>
compute_tangent_splitters(std::vector<CGAL::Point_2<CGAL::Cartesian<double>>> polygonal_chain, int i)
{
  std::vector<tangent_splitter> tangent_splitters;
  CGAL::Point_2<CGAL::Cartesian<double>> ref_point = polygonal_chain.at(i);
  for(int j = i + 1; j < polygonal_chain.size(); j++)
  {
    CGAL::Point_2<CGAL::Cartesian<double>> current_point = polygonal_chain.at(j);
    CGAL::Point_2<CGAL::Cartesian<double>> previous_point = polygonal_chain.at(j - 1);
    CGAL::Point_2<CGAL::Cartesian<double>> next_point;
    if(j == polygonal_chain.size() - 1)
    {
      next_point = previous_point;
    }
    else
    {
      next_point = polygonal_chain.at(j + 1);
    }
    tangent_type t1 = get_tangent_type({ref_point, current_point}, previous_point, next_point);
    switch(t1)
    {
      case tangent_type::minimal:
      case tangent_type::maximal:
      {
        int k = j - 1;
        CGAL::Point_2<CGAL::Cartesian<double>> p_int;
        while(!CGAL::assign(p_int,
          CGAL::intersection(CGAL::Segment_2<CGAL::Cartesian<double>> (polygonal_chain.at(i), polygonal_chain.at(j)),
            CGAL::Segment_2<CGAL::Cartesian<double>> (polygonal_chain.at(k-1), polygonal_chain.at(k)))))
        {
          k -= 1;
        }
        tangent_splitter t = {j, {p_int, polygonal_chain.at(j)}};
        tangent_splitters.push_back(t);
        break;
      }
      default:
        break;
    }
  }

  return tangent_splitters;
}

void
distribute_points(std::vector<CGAL::Point_2<CGAL::Cartesian<double>>> subdivision, int i,
  std::vector<CGAL::Point_2<CGAL::Cartesian<double>>> points_to_distribute)
{
  
}
