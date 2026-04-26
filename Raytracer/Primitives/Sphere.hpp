#pragma once

#include "../math/Ray.hpp"
#include "../Core/IObject.hpp"
#include "../Core/IMaterial.hpp"
#include "../Core/HitObject.hpp"
#include "../Core/Color.hpp"
#include "../math/MathCalculations.hpp"
#include <cmath>

namespace RayTracer {
    class Sphere : public IObject
    {
    private:
        Math::Point3D center;
        double radius;
        std::shared_ptr<IMaterial> material;
    public:
        Sphere(Math::Point3D center, double radius, std::shared_ptr<IMaterial> material): center(center), radius(radius), material(material) {};
        bool hit(const Ray& ray, HitObject &obj, double tMin, double tMax)const override {
            Math::Vector3D pointToCircleCenter = center - ray.origin;
            auto a = ray.direction.lengthSquared();
            auto h = ray.direction.dot(pointToCircleCenter);
            auto c = pointToCircleCenter.lengthSquared() - radius * radius;
            auto discriminant = h * h - a * c;
            if (discriminant < 0) {
                return false;
            }
            const double sqrtDiscriminant = std::sqrt(discriminant);
            const auto root = Math::Calc::nearestRoot(
                (h - sqrtDiscriminant) / a,
                (h + sqrtDiscriminant) / a,
                tMin,
                tMax
            );
            if (!root.hit) {
                return false;
            }
            obj.t = root.t;
            obj.point = ray.at(root.t);
            obj.normal = (obj.point - center) / radius;
            obj.material = material;
            return true;
        }
        ~Sphere() = default;
    };
}

// vec3 oc = center - r.origin();
// auto a = dot(r.direction(), r.direction());
// auto b = -2.0 * dot(r.direction(), oc);
// auto c = dot(oc, oc) - radius*radius;
// auto discriminant = b*b - 4*a*c;
// return (discriminant >= 0);
