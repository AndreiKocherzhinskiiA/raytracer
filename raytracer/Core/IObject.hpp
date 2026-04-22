#pragma once
#include "../math/Ray.hpp"
#include "HitObject.hpp"


namespace RayTracer {
    class IObject
    {
    private:
        /* data */
    public:
        virtual bool hit(const Ray& ray, double tMax, double tMin, HitObject &obj)const  = 0;
        ~IObject() = default;
    };
}

