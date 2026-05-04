#include "FlatColor.hpp"
#include "../Core/HitObject.hpp"


namespace RayTracer {
        FlatColor::FlatColor(const Color c): _color(c){};
        bool FlatColor::scatter(const Ray& rayIn, const HitObject& rec, Color& color, Ray& scattered) const {
            (void)rayIn;
            Math::Vector3D scatterDir = rec.normal + Math::Vector3D::randomUnitVector() ;

            if (scatterDir.length() < 1e-8)
                scatterDir = rec.normal;

            scattered = Ray(rec.point, scatterDir.normalize());
            color= _color;
            return true;
        };
        const Color &FlatColor::color() const {
            return _color;
        }
        // FlatColor::~FlatColor() = default;
};