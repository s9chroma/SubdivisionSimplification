#ifndef POINT_H
#define POINT_H
#pragma once

struct Point2D
{
  double x;
  double y;

  Point2D(int i, int j) : x(i), y(j) {};
};

struct Line2D
{
  Point2D p1;
  Point2D p2;

  Line2D(Point2D A, Point2D B) : p1(A), p2(B) {};
};

double
compute_angle(Line2D l1, Line2D l2);

double
radians_to_degrees(double x);

#endif
