#pragma once
#include "../math/Ray.hpp"
#include "HitObject.hpp"
#include <limits>


namespace RayTracer {
    class IObject
    {
    private:
        /* data */
    public:
        virtual bool hit(const Ray& ray, HitObject &obj, double tMin, double tMax)const  = 0;
        virtual ~IObject() = default;
    };
}

