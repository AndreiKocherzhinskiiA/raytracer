/*
** EPITECH PROJECT, 2026
** G-OOP-400-BAR-4-1-raytracer-7 [WSL: Ubuntu-24.04]
** File description:
** Cone
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
    class Cone : public IObject
    {
    private:
        Math::Point3D _center;
        double _radius;
        double _height;
        std::shared_ptr<IMaterial> _material;

    public:
        Cone(const libconfig::Setting &info);
        bool hit(const Ray& ray, HitObject &obj, double tMin, double tMax) const override;
        ~Cone() = default;
    };
}
