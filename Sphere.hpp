#pragma once

#include "RayTracer.hpp"

namespace RayTracer {
    class Sphere
    {
    private:
        /* data */
    public:
        Math::Point3D center;
        double radius;
        Sphere(Math::Point3D center, double radius): center(center), radius(radius) {};
        double hit(const Ray &ray) const {
            Math::Vector3D pointToCircleCenter = center - ray.origin;
            auto a = ray.direction.dot(ray.direction);
            auto b = -2.0 * ray.direction.dot(pointToCircleCenter);
            auto c = pointToCircleCenter.dot(pointToCircleCenter) - radius * radius;
            auto discriminant = b * b - 4 * a * c;
            if (discriminant < 0) {
                return -1;
            } else {
                return (- b - std::sqrt(discriminant) ) / (2.0 * a);
            }
        }
        ~Sphere() = default;
    };
}

// vec3 oc = center - r.origin();
// auto a = dot(r.direction(), r.direction());
// auto b = -2.0 * dot(r.direction(), oc);
// auto c = dot(oc, oc) - radius*radius;
// auto discriminant = b*b - 4*a*c;
// return (discriminant >= 0);