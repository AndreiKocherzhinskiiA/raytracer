#pragma once

#include "../math/Ray.hpp"
#include "../Core/IObject.hpp"
#include "../Core/IMaterial.hpp"
#include "../Core/HitObject.hpp"
#include "../Core/Color.hpp"

namespace RayTracer {
    class Sphere : public IObject
    {
    private:
        Math::Point3D center;
        double radius;
        std::shared_ptr<IMaterial> material;
        Color color = {0 ,0 ,0};
    public:
        Sphere(Math::Point3D center, double radius, std::shared_ptr<IMaterial> material, Color color): center(center), radius(radius), material(material), color(color) {};
        //NEED TO FIX TO WORK WITH THE NEW PROTOTYPE;
        // ray = incoming ray;
        // discriminant must be between tMax and TMin return false if not
        // obj = if you it fill with info
        bool hit(const Ray& ray, double tMax, double tMin, HitObject &obj)const override {
            Math::Vector3D pointToCircleCenter = center - ray.origin;
            auto a = ray.direction.lengthSquared();
            auto h = ray.direction.dot(pointToCircleCenter);
            auto c = pointToCircleCenter.lengthSquared() - radius * radius;
            auto discriminant = h * h - a * c;
            if (discriminant < 0) {
                return false;
            }
            double t = (-h - std::sqrt(discriminant)) / a;
            if (t < tMin || t > tMax) {
                t = (-h + std::sqrt(discriminant)) / a; // other root
                if (t < tMin || t > tMax) {
                    return false;
                }
            }
            obj.t = t;
            obj.point = ray.at(t);
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