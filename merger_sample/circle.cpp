#include "circle.h"

#include <cmath>

inline double sqr(double x) {
    return x * x;
}

bool Circle::inside(double x1, double y1) const {
    return sqr(x1 - x) + sqr(y1 - y) <= sqr(r);
}
