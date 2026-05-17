#pragma once

#include "../Core/HitObject.hpp"
#include "../Core/IMaterial.hpp"
#include "../Core/IObject.hpp"
#include "../math/Point3D.hpp"
#include "../math/Ray.hpp"
#include <memory>
#include <libconfig.h++>

namespace RayTracer {
    class Cube : public IObject
    {
    private:
        Math::Point3D _center;
        double _width;
        double _height;
        double _depth;
        Math::Vector3D _rotation = {0.0, 0.0, 0.0};
        std::shared_ptr<IMaterial> _material;

    public:
        Cube(const libconfig::Setting &info);
        bool hit(const Ray& ray, HitObject &obj, double tMin, double tMax) const override;
        ~Cube() = default;
    };
}
