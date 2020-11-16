#ifndef SUBDIV_SIMPLIFICATION_H
#define SUBDIV_SIMPLIFICATION_H

#include <CGAL/Cartesian.h>

struct shortcut
{
  CGAL::Point_2<CGAL::Cartesian<double>> start;
  CGAL::Point_2<CGAL::Cartesian<double>> end;
};

std::vector<shortcut>
compute_allowed_shortcuts(std::vector<CGAL::Point_2<CGAL::Cartesian<double>>> polygonal_chain,
                          double error);

#endif
