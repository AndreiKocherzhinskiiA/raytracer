#include "Plane.hpp"
#include "../Core/HitObject.hpp"
#include <cmath>

namespace RayTracer {
    Plane::Plane(Axis axis, double position, const Color &color, std::shared_ptr<IMaterial> material)
        : _axis(axis), _position(position), material(material), color(color)
    {
    }

    bool Plane::hit(const Ray& ray, HitObject &obj, double tMin, double tMax) const
    {
        double t;

        if (_axis == Axis::X) {
            if (std::abs(ray.direction.x) < 1e-6)
                return false;
            t = (_position - ray.origin.x) / ray.direction.x;
            obj.normal = {1, 0, 0};
        }
        else if (_axis == Axis::Y) {
            if (std::abs(ray.direction.y) < 1e-6)
                return false;
            t = (_position - ray.origin.y) / ray.direction.y;
            obj.normal = {0, 1, 0};
        }
        else {
            if (std::abs(ray.direction.z) < 1e-6)
                return false;
            t = (_position - ray.origin.z) / ray.direction.z;
            obj.normal = {0, 0, 1};
        }

        if (t < tMin || t > tMax)
            return false;

        if (obj.normal.dot(ray.direction) > 0)
            obj.normal = obj.normal * -1;
        obj.point = ray.origin + ray.direction * t;
        obj.t = t;
        obj.material = material;
        return true;
    }
}
