#pragma once

#include "Ray.hpp"
#include "Rectangle3D.hpp"

namespace RayTracer {
    class Camera
    {
    private:
        /* data */
    public:
        Math::Point3D origin = Math::Point3D(0, 0, 0);
        Rectangle3D screen;
        Ray ray(double u, double v) const {
            Math::Point3D point_on_screen = screen.pointAt(u, v);
            Ray newRay;
            newRay.origin = origin;
            newRay.direction = Math::Vector3D(
                point_on_screen.x - origin.x,
                point_on_screen.y - origin.y,
                point_on_screen.z - origin.z
            );
            return newRay;
        }
        Camera(/* args */) = default;
        ~Camera()= default;
    };
}
