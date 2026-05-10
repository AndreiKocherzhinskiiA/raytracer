#include "Cube.hpp"
#include <algorithm>
#include <cmath>

namespace {
    bool updateSlab(
        double origin,
        double direction,
        double minBound,
        double maxBound,
        const Math::Vector3D &negativeNormal,
        const Math::Vector3D &positiveNormal,
        double &nearT,
        double &farT,
        Math::Vector3D &nearNormal,
        Math::Vector3D &farNormal
    ) {
        if (std::abs(direction) < 1e-8)
            return origin >= minBound && origin <= maxBound;

        double t0 = (minBound - origin) / direction;
        double t1 = (maxBound - origin) / direction;
        Math::Vector3D n0 = negativeNormal;
        Math::Vector3D n1 = positiveNormal;

        if (t0 > t1) {
            std::swap(t0, t1);
            std::swap(n0, n1);
        }
        if (t0 > nearT) {
            nearT = t0;
            nearNormal = n0;
        }
        if (t1 < farT) {
            farT = t1;
            farNormal = n1;
        }
        return nearT <= farT;
    }
}

namespace RayTracer {
    Cube::Cube(const Math::Point3D &center, double width, double height, double depth, std::shared_ptr<IMaterial> material)
        : _center(center), _width(width), _height(height), _depth(depth), _material(material)
    {
    }

    bool Cube::hit(const Ray& ray, HitObject &obj, double tMin, double tMax) const
    {
        Math::Point3D minBound(
            _center.x - _width / 2.0,
            _center.y - _height / 2.0,
            _center.z - _depth / 2.0
        );
        Math::Point3D maxBound(
            _center.x + _width / 2.0,
            _center.y + _height / 2.0,
            _center.z + _depth / 2.0
        );
        double nearT = tMin;
        double farT = tMax;
        Math::Vector3D nearNormal;
        Math::Vector3D farNormal;

        if (!updateSlab(ray.origin.x, ray.direction.x, minBound.x, maxBound.x, {-1, 0, 0}, {1, 0, 0}, nearT, farT, nearNormal, farNormal))
            return false;
        if (!updateSlab(ray.origin.y, ray.direction.y, minBound.y, maxBound.y, {0, -1, 0}, {0, 1, 0}, nearT, farT, nearNormal, farNormal))
            return false;
        if (!updateSlab(ray.origin.z, ray.direction.z, minBound.z, maxBound.z, {0, 0, -1}, {0, 0, 1}, nearT, farT, nearNormal, farNormal))
            return false;

        double t = nearT;
        Math::Vector3D normal = nearNormal;
        if (t < tMin) {
            t = farT;
            normal = farNormal;
        }
        if (t < tMin || t > tMax)
            return false;

        obj.t = t;
        obj.point = ray.at(t);
        obj.normal = normal;
        obj.material = _material;
        return true;
    }
}
