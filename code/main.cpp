#include <stdio.h>
#include <CGAL/Cartesian.h>
#include <CGAL/intersections.h>

#include "math_util.h"
#include "subdiv_simplification.h"

#define SIMPL_ERROR 1.2

int
main(void)
{
  /*CGAL::Point_2<CGAL::Cartesian<double>> p(0.0, 0.0), q(2.0, 2.0), r(4.0, 1.5), s(6.0, 4.0), t(8.0, 3.0), u(-22.0, 0.0);
  std::vector<CGAL::Point_2<CGAL::Cartesian<double>>> polygonal_chain = {p, q, r, s, t};
  std::vector<shortcut> shortcuts = compute_allowed_shortcuts(polygonal_chain, SIMPL_ERROR);

  for(shortcut s:shortcuts)
  {
    printf("Shortcut from (%f, %f) to (%f, %f)\n", s.start.x(), s.start.y(), s.end.x(), s.end.y());
  }*/

  CGAL::Point_2<CGAL::Cartesian<double>> p(0.0, 0.0), q(2.0, 3.0), r(4.0, 4.0), s(6.0, 2.7), t(7.0, -1.0), u(8.5, -2.5),
                                          v(10.0, 1.5), w(11.0, -1.2), x(12.0, 2.3), y(13.0, 5.0), z(26.0, 10.0);
  std::vector<CGAL::Point_2<CGAL::Cartesian<double>>> polygonal_chain = {p, q, r, s, t, u, v, w, x, y};
  std::vector<tangent_splitter> tangent_splitters = compute_tangent_splitters(polygonal_chain, 0);

  for(tangent_splitter ts: tangent_splitters)
  {
    printf("Tangent splitter for %d: from (%f, %f) to (%f, %f)\n", ts.point_index, ts.t.start.x(), ts.t.start.y(), ts.t.end.x(), ts.t.end.y());
  }
}
