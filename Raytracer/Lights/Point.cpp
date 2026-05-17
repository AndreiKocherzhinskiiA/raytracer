#include "Point.hpp"
#include "../Core/HitObject.hpp"
#include "../Scene/Scene.hpp"
#include <algorithm>
#include <algorithm>

namespace RayTracer {
    PointLight::PointLight(const libconfig::Setting& s)
    {
        double x = 0, y = 0, z = 0;
        double r = 1.0, g = 1.0, b = 1.0;

        s.lookupValue("x", x);
        s.lookupValue("y", y);
        s.lookupValue("z", z);

        if (s.exists("color")) {
            const auto& c = s["color"];
            c.lookupValue("r", r);
            c.lookupValue("g", g);
            c.lookupValue("b", b);
        }

        _pos = Math::Point3D(x, y, z);
        _color = Color(r / 255.0, g / 255.0, b / 255.0);
    }


    Math::Vector3D PointLight::directionFrom(const Math::Point3D& point) const {
        return (_pos - point).normalize();
    }

    double PointLight::maxDistanceFrom(const Math::Point3D& point) const {
        return (_pos - point).length();
    }

    void PointLight::light(const HitObject& obj, Color& color, const Scene& scene) const {
        Math::Vector3D lightDir = directionFrom(obj.point);
        double diff = std::max(0.0, obj.normal.dot(lightDir));
        // double dist = (_pos - obj.point).length();
        // double att = 1.0 / (1.0 + 0.005 * dist * dist);
        color = color + (obj.material->color() * _color * diff * scene.diffuse());
    }
}
extern "C" RayTracer::ILight *Create(const libconfig::Setting &s)
{
    return new RayTracer::PointLight(s);
}
