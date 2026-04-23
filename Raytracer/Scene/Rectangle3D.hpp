#pragma once

#include "../math/Point3D.hpp"
#include "../math/Vector3D.hpp"

class Rectangle3D {
public:
    Math::Point3D  origin;
    Math::Vector3D bottom_side;
    Math::Vector3D left_side;

    Rectangle3D(): origin(-2, -1.5, -1), bottom_side(4, 0, 0), left_side(0, 3, 0) {}

    Rectangle3D(Math::Point3D origin, Math::Vector3D bottom_side, Math::Vector3D left_side)
        : origin(origin), bottom_side(bottom_side), left_side(left_side) {}

    ~Rectangle3D() = default;

    Math::Point3D pointAt(double u, double v) const {
        return origin + bottom_side * u + left_side * v;
    }
};