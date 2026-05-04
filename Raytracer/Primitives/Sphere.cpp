#include "Sphere.hpp"
#include "../Core/HitObject.hpp"
#include <cmath>

namespace RayTracer {
    Sphere::Sphere(const Math::Point3D &center, double radius, const Color &color)
        : center(center), radius(radius), color(color)
    {
        material = std::make_shared<FlatColor>(color);
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