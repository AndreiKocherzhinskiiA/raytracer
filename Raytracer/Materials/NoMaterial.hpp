#pragma once
#include "../Core/IMaterial.hpp"


namespace RayTracer {
    class NoMaterial : public IMaterial
    {
    private:
        /* data */
        Color _color;
    public:
        NoMaterial(const Color c): _color(c){};
        bool scatter(const Ray& rayIn, const HitObject& rec, Color& color, Ray& scattered) const {
            (void)rayIn;
            (void)rec;
            (void)color;
            (void)scattered;
            color = _color;
            return true;}
        const Color &color() const {
            return _color;
        }
        ~NoMaterial() = default;
    };
}