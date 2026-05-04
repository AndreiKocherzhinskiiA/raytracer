#pragma once
#include "../Core/IMaterial.hpp"


namespace RayTracer {
    class NoMaterial : public IMaterial
    {
    private:
        Color _color;
    public:
        NoMaterial(const Color c): _color(c){};
        bool scatter(const Ray& rayIn, const HitObject& rec, Color& color, Ray& scattered) const {

            color = _color;
            return false;}
        const Color &color() const {
            return _color;
        }
        ~NoMaterial() = default;
    };
}