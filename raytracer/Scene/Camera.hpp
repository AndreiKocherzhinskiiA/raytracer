#pragma once

#include "Ray.hpp"
#include "Rectangle3D.hpp"

namespace RayTracer {

class Camera {
public:
    int image_width;
    int image_height;
    Math::Point3D origin;
    Rectangle3D screen;

    Camera() = default;

    Camera(Math::Point3D origin, Rectangle3D screen)
        : origin(origin), screen(screen) {}

    Ray ray(double u, double v) const {
        Math::Point3D pixel = screen.pointAt(u, v);
        Math::Vector3D direction = (pixel - origin).normalize();
        return Ray(origin, direction);
    }

    ~Camera() = default;
};

} // namespace RayTracer