#include "Directional.hpp"
#include "../Core/HitObject.hpp"
#include "../Scene/Scene.hpp"
#include "../Core/Constants.hpp"
#include <algorithm>


namespace RayTracer {

    Directional::Directional(const libconfig::Setting& s)
    {
        double x = 0;
        double y = 0;
        double z = 0;
        double r = 1.0;
        double g = 1.0;
        double b = 1.0;

        s.lookupValue("x", x);
        s.lookupValue("y", y);
        s.lookupValue("z", z);

        if (s.exists("color")) {
            const auto& c = s["color"];
            c.lookupValue("r", r);
            c.lookupValue("g", g);
            c.lookupValue("b", b);
        }

        _dir = Math::Vector3D(x, y, z).normalize();
        _color = Color(r / 255.0, g / 255.0, b / 255.0);
    }


    Math::Vector3D Directional::directionFrom(const Math::Point3D& point) const {
        (void)point;
        return Math::Vector3D(-_dir.x, -_dir.y, -_dir.z);
    }

    double Directional::maxDistanceFrom(const Math::Point3D& point) const {
        (void)point;
        return infinity;
    }

    void Directional::light(const HitObject& obj, Color& color, const Scene& scene) const {
        Math::Vector3D lightDir = directionFrom(obj.point).normalize();
        double diff = std::max(0.0, obj.normal.dot(lightDir));
        color = color + (obj.material->color() * _color * diff * scene.diffuse());
    }

}
extern "C" RayTracer::ILight *Create(const libconfig::Setting &s)
{
    return new RayTracer::Directional(s);
}
