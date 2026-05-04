#pragma once
#include "../math/Point3D.hpp"
#include "../math/Vector3D.hpp"
#include "Color.hpp"

namespace RayTracer {
    struct HitObject;
    class Scene;

    class ILight
    {
    public:
        virtual Math::Vector3D directionFrom(const Math::Point3D& point) const = 0;
        virtual double maxDistanceFrom(const Math::Point3D& point) const = 0;
        virtual void light(const HitObject& obj, Color& color, const Scene& scene) const = 0;
        virtual ~ILight() = default;
    };
}