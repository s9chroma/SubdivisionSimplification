#include <stdio.h>
#include <CGAL/Cartesian.h>

#include "math_util.h"
#include "subdiv_simplification.h"

#define SIMPL_ERROR 1.2

int
main(void)
{
  CGAL::Point_2<CGAL::Cartesian<double>> p(0.0, 0.0), q(2.0, 2.0), r(4.0, 1.5), s(6.0, 4.0), t(8.0, 3.0), u(-22.0, 0.0);
  std::vector<CGAL::Point_2<CGAL::Cartesian<double>>> polygonal_chain = {p, q, r, s, t};
  std::vector<shortcut> shortcuts = compute_allowed_shortcuts(polygonal_chain, SIMPL_ERROR);

  for(shortcut s:shortcuts)
  {
    printf("Shortcut from (%f, %f) to (%f, %f)\n", s.start.x(), s.start.y(), s.end.x(), s.end.y());
  }
}
