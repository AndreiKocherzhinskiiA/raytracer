#pragma once

#include "../Core/IMaterial.hpp"
#include <libconfig.h++>

namespace RayTracer {
    class Reflection : public IMaterial
    {
    private:
        Color _color;

    public:
        Reflection(const libconfig::Setting& s);
        bool scatter(const Ray& rayIn, const HitObject& rec, Color& color, Ray& scattered) const override;
        const Color& color() const override;
        ~Reflection() = default;
    };
}
