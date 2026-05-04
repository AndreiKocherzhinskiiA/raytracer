#pragma once
#include <limits>

namespace RayTracer {
    inline constexpr double epsilon = 1e-8;
    inline constexpr double infinity = std::numeric_limits<double>::infinity();
}