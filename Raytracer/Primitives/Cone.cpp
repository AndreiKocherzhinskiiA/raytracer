/*
** EPITECH PROJECT, 2026
** G-OOP-400-BAR-4-1-raytracer-7 [WSL: Ubuntu-24.04]
** File description:
** Cone
*/

#include "Cone.hpp"
#include <cmath>
#include "../Scene/Factory.hpp"

namespace RayTracer {
    Cone::Cone(const libconfig::Setting &s)
{
    int x = 0, y = 0, z = 0;

    double radius = 1;
    double height = 1;

    std::string materialName = "flat";

    s.lookupValue("x", x);
    s.lookupValue("y", y);
    s.lookupValue("z", z);

    s.lookupValue("radius", radius);
    s.lookupValue("height", height);

    s.lookupValue("material", materialName);

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

        double minY = _center.y - _height / 2.0;
        double maxY = _center.y + _height / 2.0;
        double slope = _radius / _height;
        double slope2 = slope * slope;
        double ox = ray.origin.x - _center.x;
        double oz = ray.origin.z - _center.z;
        double apexToOriginY = maxY - ray.origin.y;
        double a = ray.direction.x * ray.direction.x
            + ray.direction.z * ray.direction.z
            - slope2 * ray.direction.y * ray.direction.y;
        double halfB = ox * ray.direction.x
            + oz * ray.direction.z
            + slope2 * apexToOriginY * ray.direction.y;
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
                    Math::Point3D p = ray.at(t);
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

        if (std::abs(ray.direction.y) >= 1e-8) {
            double t = (minY - ray.origin.y) / ray.direction.y;
            Math::Point3D p = ray.at(t);
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

        if (ray.direction.dot(normal) > 0.0)
            obj.normal = normal * -1.0;
        else
            obj.normal = normal;

        obj.material = _material;
        return true;
    }
}
