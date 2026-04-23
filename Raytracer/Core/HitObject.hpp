#pragma once
#include "../math/Point3D.hpp"
#include "../math/Vector3D.hpp"
#include "IMaterial.hpp"

#include <memory>

struct HitObject
{
    Math::Point3D point;
    Math::Vector3D normal;
    double t; //at what distance it hits
    std::shared_ptr<RayTracer::IMaterial> material;
};
