#pragma once

#include "Point3D.hpp"
#include "Vector3D.hpp"


namespace RayTracer {
    class Ray
    {
    private:
        /* data */
    public:
        Math::Point3D origin;
        Math::Vector3D direction;
        Ray(/* args */) = default;
        Ray(Math::Point3D origin, Math::Vector3D direction): origin(origin), direction(direction){};
        ~Ray() = default;
    };
}

