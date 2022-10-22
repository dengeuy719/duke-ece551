#include "circle.hpp"

#include <cmath>
#include <cstdlib>
double Circle::intersectionArea(const Circle & otherCircle) {
  double distance = center.distanceFrom(otherCircle.center);
  double r1 = radius, r2 = otherCircle.radius;
  double s, l;
  if (r1 >= r2) {
    l = r1;
    s = r2;
  }
  else {
    l = r2;
    s = r1;
  }

  if (distance >= l + s) {
    return 0.0;
  }
  else if (distance <= l - s) {
    return M_PI * s * s;
  }
  else {
    double a1 = std::acos((s * s - l * l + distance * distance) / (2 * distance * s));
    double a2 = std::acos((l * l - s * s + distance * distance) / (2 * distance * l));
    double ans = a1 * s * s + a2 * l * l - s * distance * std::sin(a1);
    return ans;
  }
}
void Circle::move(double dx, double dy) {
  center.move(dx, dy);
}
