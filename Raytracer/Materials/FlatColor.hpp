#pragma once
#include "../Core/IMaterial.hpp"


namespace RayTracer {
    class FlatColor : public IMaterial
    {
    private:
        Color _color;
    public:
        FlatColor(const Color c): _color(c){};
        bool scatter(const Ray& rayIn, const HitObject& rec, Color& color, Ray& scattered) const {
            (void)rayIn;
            (void)rec;
            (void)color;
            (void)scattered;
            color = _color;
            return false;}
        const Color &color() const {
            return _color;
        }
        ~FlatColor() = default;
    };
}