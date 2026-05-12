#pragma once

#include "../math/Ray.hpp"
#include "../Core/IObject.hpp"
#include "../Core/IMaterial.hpp"
#include "../Core/HitObject.hpp"
#include "../Core/Color.hpp"
#include "../Materials/FlatColor.hpp"
#include "../Materials/Reflection.hpp"
#include <iostream>
#include <libconfig.h++>
#include <memory>

enum class Axis {
    X,
    Y,
    Z
};

namespace RayTracer {
    class Plane : public IObject
    {
    private:
        Axis _axis;
        double _position;
        std::shared_ptr<IMaterial> material;
        Color color = {0, 0, 0};

    public:
        Plane(const libconfig::Setting &info);
        bool hit(const Ray& ray, HitObject &obj, double tMin, double tMax) const override;
        ~Plane() = default;
    };
}