#pragma once

#include "../math/Ray.hpp"
#include "../Core/IObject.hpp"
#include "../Core/IMaterial.hpp"
#include "../Core/HitObject.hpp"
#include "../Core/Color.hpp"
#include "../Materials/NoMaterial.hpp"
#include <iostream>

namespace RayTracer {
    class Sphere : public IObject
    {
    private:
        Math::Point3D center;
        double radius;
        std::shared_ptr<IMaterial> material;
        Color color = {0 ,0 ,0};

    public:
        Sphere(const Math::Point3D &center, double radius, 
            const Color &color): center(center), radius(radius), color(color) {
                material = std::make_shared<NoMaterial>(color);
            }
        //NEED TO FIX TO WORK WITH THE NEW PROTOTYPE;
        // ray = incoming ray;
        // discriminant must be between tMax and TMin return false if not
        // obj = if you it fill with info
        bool hit(const Ray& ray, HitObject &obj, double tMin,  double tMax) const override 
        {
            Math::Vector3D oc = ray.origin - center;
            auto a = ray.direction.lengthSquared();
            auto h = ray.direction.dot(oc);
            auto c = oc.lengthSquared() - radius * radius;

            auto discriminant = h * h - a * c;
            if (discriminant < 0)
                return false;

            double sqrtD = (std::sqrt(discriminant));

            auto t = (-h - sqrtD) / a;
            if (t < tMin || t > tMax) {
                t = (-h + sqrtD) / a; // other root
                if (t < tMin || t > tMax) {
                    return false;
                }
            }
            // std::cout << "hit" << std::endl;
            obj.t = t;
            obj.point = ray.at(t);
            Math::Vector3D outward_normal = ((obj.point - center) / radius).normalize();
            if (ray.direction.dot(outward_normal) > 0.0) {
                obj.normal = outward_normal * -1.0;
            } else {
                obj.normal = outward_normal;
            }
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
//std::shared_ptr<IMaterial> material, 