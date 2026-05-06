/*
** EPITECH PROJECT, 2026
** G-OOP-400-BAR-4-1-raytracer-7 [WSL: Ubuntu-24.04]
** File description:
** Cylinder
*/

#pragma once

#include "../Core/Color.hpp"
#include "../Core/HitObject.hpp"
#include "../Core/IMaterial.hpp"
#include "../Core/IObject.hpp"
#include "../Materials/FlatColor.hpp"
#include "../math/Point3D.hpp"
#include "../math/Ray.hpp"
#include <memory>

namespace RayTracer {
    class Cylinder : public IObject
    {
    private:
        Math::Point3D _center;
        double _radius;
        double _height;
        std::shared_ptr<IMaterial> _material;

    public:
        Cylinder(const Math::Point3D &center, double radius, double height, const Color &color);
        bool hit(const Ray& ray, HitObject &obj, double tMin, double tMax) const override;
        ~Cylinder() = default;
    };
}
