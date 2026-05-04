#pragma once
#include "../math/Point3D.hpp"
#include "../math/Vector3D.hpp"
#include "IMaterial.hpp"
#include <memory>

namespace RayTracer {
    struct HitObject
    {
        Math::Point3D point;
        Math::Vector3D normal;
        double t;
        std::shared_ptr<IMaterial> material;
    };
}