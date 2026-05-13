#include "FlatColor.hpp"
#include "../Core/HitObject.hpp"


namespace RayTracer {
        FlatColor::FlatColor(const Color c): _color(c){};
        bool FlatColor::scatter(const Ray& rayIn, const HitObject& rec, Color& color, Ray& scattered) const {
            (void)rayIn;
            (void)rec;
            (void)color;
            (void)scattered;
            return false; // was true
        };
        const Color &FlatColor::color() const {
            return _color;
        }
        // FlatColor::~FlatColor() = default;
};

