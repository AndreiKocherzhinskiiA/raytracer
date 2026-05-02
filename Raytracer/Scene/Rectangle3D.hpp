#pragma once
#include "../math/Point3D.hpp"
#include "../math/Vector3D.hpp"

namespace RayTracer {

class Rectangle3D {
public:
    Math::Point3D  origin;
    Math::Vector3D u_axis;
    Math::Vector3D v_axis;

    Rectangle3D(): origin(-2, -1.5, -1), u_axis( 4,  0,  0), v_axis( 0, -3,  0) {}

    Rectangle3D(Math::Point3D  origin, Math::Vector3D u_axis, Math::Vector3D v_axis)
        : origin(origin), u_axis(u_axis), v_axis(v_axis) {}

    ~Rectangle3D() = default;

    Math::Point3D pointAt(double u, double v) const {
        return origin + u_axis * u + v_axis * v;
    }
};

} // namespace RayTracer