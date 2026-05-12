#include "Sphere.hpp"
#include "../Core/HitObject.hpp"
#include <cmath>

namespace RayTracer {

    Sphere::Sphere(const libconfig::Setting &s)
    {
        int x = 0, y = 0, z = 0;
        int r = 0;
        int cr = 255, cg = 255, cb = 255;
        std::string material = "flat";

        s.lookupValue("x", x);
        s.lookupValue("y", y);
        s.lookupValue("z", z);
        s.lookupValue("r", r);
        s.lookupValue("material", material);

        if (s.exists("color")) {
            const auto &c = s["color"];
            c.lookupValue("r", cr);
            c.lookupValue("g", cg);
            c.lookupValue("b", cb);
        }

        center = Math::Point3D(x, y, z);
        radius = r;
        color = Color(cr / 255.0, cg / 255.0, cb / 255.0);

        if (material == "flat") {
            this->material = std::make_shared<FlatColor>(color);
        }
    }
    
    bool Sphere::hit(const Ray& ray, HitObject &obj, double tMin, double tMax) const
    {
        Math::Vector3D oc = ray.origin - center;
        auto a = ray.direction.lengthSquared();
        auto h = ray.direction.dot(oc);
        auto c = oc.lengthSquared() - radius * radius;

        auto discriminant = h * h - a * c;
        if (discriminant < 0)
            return false;

        double sqrtD = std::sqrt(discriminant);

        auto t = (-h - sqrtD) / a;
        if (t < tMin || t > tMax) {
            t = (-h + sqrtD) / a;
            if (t < tMin || t > tMax)
                return false;
        }

        obj.t = t;
        obj.point = ray.at(t);

        Math::Vector3D outward_normal = ((obj.point - center) / radius).normalize();

        if (ray.direction.dot(outward_normal) > 0.0)
            obj.normal = outward_normal * -1.0;
        else
            obj.normal = outward_normal;

        obj.material = material;
        return true;
    }
}