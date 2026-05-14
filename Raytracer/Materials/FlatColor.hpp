#pragma once
#include "../Core/IMaterial.hpp"
#include <libconfig.h++>



namespace RayTracer {
    class FlatColor : public IMaterial
    {
    private:
        Color _color;
    public:
        FlatColor(const Color c);
        FlatColor(const libconfig::Setting& s); 
        bool scatter(const Ray& rayIn, const HitObject& rec, Color& color, Ray& scattered) const;
        const Color& color() const;
        // ~FlatColor() = default;
    };
};

extern "C" RayTracer::IMaterial *Create(const libconfig::Setting &s)
 {
     return new RayTracer::FlatColor(s);
 }