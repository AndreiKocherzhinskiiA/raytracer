#pragma once
#include "../math/Ray.hpp"
#include "HitObject.hpp"
#include "Color.hpp"
class HitObject;

namespace RayTracer {
    class IMaterial
    {
    private:
        /* data */
    public:
        virtual bool scatter(const Ray& rayIn, const HitObject& rec, Color& color, Ray& scattered) const = 0;
        virtual Color color() const;
        ~IMaterial() = default;
    };
}
