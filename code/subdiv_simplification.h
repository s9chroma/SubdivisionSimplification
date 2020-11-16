#ifndef SUBDIV_SIMPLIFICATION_H
#define SUBDIV_SIMPLIFICATION_H

#include <CGAL/Cartesian.h>

struct line
{
  CGAL::Point_2<CGAL::Cartesian<double>> start;
  CGAL::Point_2<CGAL::Cartesian<double>> end;
};

typedef line shortcut, tangent;

struct tangent_splitter
{
  int point_index;
  tangent t;
};

enum tangent_type {maximal ,minimal, neither};

tangent_type
get_tangent_type(line l, CGAL::Point_2<CGAL::Cartesian<double>> p1,
    CGAL::Point_2<CGAL::Cartesian<double>> p2);

std::vector<shortcut>
compute_allowed_shortcuts(std::vector<CGAL::Point_2<CGAL::Cartesian<double>>> polygonal_chain,
                          double error);

std::vector<tangent_splitter>
compute_tangent_splitters(std::vector<CGAL::Point_2<CGAL::Cartesian<double>>> polygonal_chain, int i);

std::vector<tangent_splitter>
distribute_points(std::vector<CGAL::Point_2<CGAL::Cartesian<double>>> subdivision, int i,
  std::vector<CGAL::Point_2<CGAL::Cartesian<double>>> points_to_distribute);

#endif
