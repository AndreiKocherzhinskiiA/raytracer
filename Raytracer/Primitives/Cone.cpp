/*
** EPITECH PROJECT, 2026
** G-OOP-400-BAR-4-1-raytracer-7 [WSL: Ubuntu-24.04]
** File description:
** Cone
*/

#include "Cone.hpp"
#include <cmath>
#include "../Scene/Factory.hpp"
#include "../math/Transform.hpp"

namespace RayTracer {
    Cone::Cone(const libconfig::Setting &s)
{
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;

    double radius = 1;
    double height = 1;

    std::string materialName = "flat";

    s.lookupValue("x", x);
    s.lookupValue("y", y);
    s.lookupValue("z", z);

    s.lookupValue("radius", radius);
    s.lookupValue("height", height);

    s.lookupValue("material", materialName);
    if (s.exists("rotation")) {
        const auto &rotation = s["rotation"];
        rotation.lookupValue("x", _rotation.x);
        rotation.lookupValue("y", _rotation.y);
        rotation.lookupValue("z", _rotation.z);
    }

    _center = Math::Point3D(x, y, z);
    _radius = radius;
    _height = height;

    const auto &mat = s["material"];
    std::string type = "flatcolor";
    mat.lookupValue("type", type);

    _material = Factory<IMaterial>::create(type, mat);
    
}

    bool Cone::hit(const Ray& ray, HitObject &obj, double tMin, double tMax) const
    {
        if (_height <= 0 || _radius <= 0)
            return false;

        Ray localRay(
            _center + Math::inverseRotateVector(ray.origin - _center, _rotation),
            Math::inverseRotateVector(ray.direction, _rotation)
        );
        double minY = _center.y - _height / 2.0;
        double maxY = _center.y + _height / 2.0;
        double slope = _radius / _height;
        double slope2 = slope * slope;
        double ox = localRay.origin.x - _center.x;
        double oz = localRay.origin.z - _center.z;
        double apexToOriginY = maxY - localRay.origin.y;
        double a = localRay.direction.x * localRay.direction.x
            + localRay.direction.z * localRay.direction.z
            - slope2 * localRay.direction.y * localRay.direction.y;
        double halfB = ox * localRay.direction.x
            + oz * localRay.direction.z
            + slope2 * apexToOriginY * localRay.direction.y;
        double c = ox * ox + oz * oz - slope2 * apexToOriginY * apexToOriginY;
        bool hitAnything = false;
        double closest = tMax;
        Math::Vector3D normal;

        if (std::abs(a) >= 1e-8) {
            double discriminant = halfB * halfB - a * c;
            if (discriminant >= 0) {
                double sqrtD = std::sqrt(discriminant);
                double roots[2] = {
                    (-halfB - sqrtD) / a,
                    (-halfB + sqrtD) / a
                };

                for (double t : roots) {
                    Math::Point3D p = localRay.at(t);
                    if (t >= tMin && t <= closest && p.y >= minY && p.y <= maxY) {
                        double q = maxY - p.y;

                        hitAnything = true;
                        closest = t;
                        normal = Math::Vector3D(
                            p.x - _center.x,
                            slope2 * q,
                            p.z - _center.z
                        ).normalize();
                    }
                }
            }
        }

        if (std::abs(localRay.direction.y) >= 1e-8) {
            double t = (minY - localRay.origin.y) / localRay.direction.y;
            Math::Point3D p = localRay.at(t);
            double dx = p.x - _center.x;
            double dz = p.z - _center.z;

            if (t >= tMin && t <= closest && dx * dx + dz * dz <= _radius * _radius) {
                hitAnything = true;
                closest = t;
                normal = {0, -1, 0};
            }
        }

        if (!hitAnything)
            return false;

        obj.t = closest;
        obj.point = ray.at(closest);
        normal = Math::rotateVector(normal, _rotation).normalize();

        if (ray.direction.dot(normal) > 0.0)
            obj.normal = normal * -1.0;
        else
            obj.normal = normal;

        obj.material = _material;
        return true;
    }
}

extern "C" RayTracer::IObject *Create(const libconfig::Setting &s)
{
    return new RayTracer::Cone(s);
}
