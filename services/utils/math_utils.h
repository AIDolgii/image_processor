#ifndef MATH_UTILS_H
#define MATH_UTILS_H

#include <algorithm>
#include <cstdint>
#include <functional>
#include <random>
#include <string>
#include "cache.h"

namespace utils {
struct Point {
    float x;
    float y;
};

struct Quadrangle {
    Point a;
    Point b;
    Point c;
    Point d;
    Point GetMin() const;
    Point GetMax() const;
};

using Plane = std::vector<std::vector<Point>>;

int RoundUp(int num, int multiple);

Plane GeneratePointsWithOffset(size_t width, size_t height, int step, float offset_delta);

std::vector<Quadrangle> GenerateQuadrangles(const Plane& plane);

bool IsPointInQuadrangle(const Point& p, const Quadrangle& q);

bool IsSuitableType(std::string_view value, std::string_view type);
}  // namespace utils

#endif  // MATH_UTILS_H
