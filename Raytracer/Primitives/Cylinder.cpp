/*
** EPITECH PROJECT, 2026
** G-OOP-400-BAR-4-1-raytracer-7 [WSL: Ubuntu-24.04]
** File description:
** Cylinder
*/

#include "Cylinder.hpp"
#include "../Scene/Factory.hpp"
#include <cmath>

namespace RayTracer {
    Cylinder::Cylinder(const libconfig::Setting &s)
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

    bool Cylinder::hit(const Ray& ray, HitObject &obj, double tMin, double tMax) const
    {
        Math::Vector3D oc = ray.origin - _center;
        double a = ray.direction.x * ray.direction.x + ray.direction.z * ray.direction.z;
        double halfB = oc.x * ray.direction.x + oc.z * ray.direction.z;
        double c = oc.x * oc.x + oc.z * oc.z - _radius * _radius;
        double minY = _center.y - _height / 2.0;
        double maxY = _center.y + _height / 2.0;
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
                    double y = ray.at(t).y;
                    if (t >= tMin && t <= closest && y >= minY && y <= maxY) {
                        hitAnything = true;
                        closest = t;
                        normal = {
                            (ray.at(t).x - _center.x) / _radius,
                            0,
                            (ray.at(t).z - _center.z) / _radius
                        };
                    }
                }
            }
        }

        if (std::abs(ray.direction.y) >= 1e-8) {
            double capYs[2] = {minY, maxY};
            Math::Vector3D capNormals[2] = {
                {0, -1, 0},
                {0, 1, 0}
            };

            for (int i = 0; i < 2; i++) {
                double t = (capYs[i] - ray.origin.y) / ray.direction.y;
                Math::Point3D p = ray.at(t);
                double dx = p.x - _center.x;
                double dz = p.z - _center.z;

                if (t >= tMin && t <= closest && dx * dx + dz * dz <= _radius * _radius) {
                    hitAnything = true;
                    closest = t;
                    normal = capNormals[i];
                }
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
