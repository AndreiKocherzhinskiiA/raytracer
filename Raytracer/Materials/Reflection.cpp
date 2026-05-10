#include "Reflection.hpp"
#include "../Core/Constants.hpp"
#include "../Core/HitObject.hpp"

namespace RayTracer {
    Reflection::Reflection(const Color &color): _color(color) {}

    bool Reflection::scatter(const Ray& rayIn, const HitObject& rec, Color& color, Ray& scattered) const
    {
        Math::Vector3D incoming = rayIn.direction.normalize();
        Math::Vector3D reflected = incoming - rec.normal * (2.0 * incoming.dot(rec.normal));

        scattered = Ray(rec.point + rec.normal * epsilon, reflected.normalize());
        color = _color;
        return reflected.dot(rec.normal) > 0.0;
    }

    const Color& Reflection::color() const
    {
        return _color;
    }
}
