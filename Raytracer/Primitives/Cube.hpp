#pragma once

#include "../Core/HitObject.hpp"
#include "../Core/IMaterial.hpp"
#include "../Core/IObject.hpp"
#include "../math/Point3D.hpp"
#include "../math/Ray.hpp"
#include <memory>

namespace RayTracer {
    class Cube : public IObject
    {
    private:
        Math::Point3D _center;
        double _width;
        double _height;
        double _depth;
        std::shared_ptr<IMaterial> _material;

    public:
        Cube(const Math::Point3D &center, double width, double height, double depth, std::shared_ptr<IMaterial> material);
        bool hit(const Ray& ray, HitObject &obj, double tMin, double tMax) const override;
        ~Cube() = default;
    };
}
