#pragma once
#include "../Core/IMaterial.hpp"



namespace RayTracer {
    class FlatColor : public IMaterial
    {
    private:
        Color _color;
    public:
        FlatColor(const Color c);
        bool scatter(const Ray& rayIn, const HitObject& rec, Color& color, Ray& scattered) const;
        const Color& color() const;
        // ~FlatColor() = default;
    };
};