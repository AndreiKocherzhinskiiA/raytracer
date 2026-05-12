#pragma once

#include "../math/Ray.hpp"
#include "../Core/IObject.hpp"
#include "../Core/IMaterial.hpp"
#include "../Core/HitObject.hpp"
#include "../Core/Color.hpp"
#include "../Materials/FlatColor.hpp"
#include "../Materials/Reflection.hpp"
#include <libconfig.h++>
#include <iostream>
#include <memory>

namespace RayTracer {
    class Sphere : public IObject
    {
    private:
        Math::Point3D center;
        double radius;
        std::shared_ptr<IMaterial> material;
        Color color = {0, 0, 0};

    public:
        Sphere(const libconfig::Setting &info);
        bool hit(const Ray& ray, HitObject &obj, double tMin, double tMax) const override;
        ~Sphere() = default;
    };
}
