#pragma once
#include "../math/Ray.hpp"
#include "Color.hpp"

namespace RayTracer {
    struct HitObject;

    class IMaterial
    {
    public:
        virtual bool scatter(const Ray& rayIn, const HitObject& rec, Color& color, Ray& scattered) const = 0;
        virtual const Color& color() const = 0;
        virtual ~IMaterial() = default;
    };
}   