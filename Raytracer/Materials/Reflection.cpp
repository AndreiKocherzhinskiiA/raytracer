#include "Reflection.hpp"
#include "../Core/Constants.hpp"
#include "../Core/HitObject.hpp"

namespace RayTracer {
    Reflection::Reflection(const libconfig::Setting &s)
    {
        double r = 255.0, g = 255.0, b = 255.0;

    if (s.exists("color")) {
        const auto &c = s["color"];
        c.lookupValue("r", r);
        c.lookupValue("g", g);
        c.lookupValue("b", b);
    }
    _color = Color(r / 255.0, g / 255.0, b / 255.0);
    }

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

extern "C" RayTracer::IMaterial *Create(const libconfig::Setting &s)
{
    return new RayTracer::Reflection(s);
}
