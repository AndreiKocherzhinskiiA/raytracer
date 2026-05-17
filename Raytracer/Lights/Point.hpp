#pragma once
#include "../Core/ILight.hpp"
#include <libconfig.h++>

namespace RayTracer {
    class PointLight : public ILight {
    private:
        Math::Point3D _pos;
        Color _color;

    public:
        PointLight(const libconfig::Setting& s);
        Math::Vector3D directionFrom(const Math::Point3D& point) const override;
        double maxDistanceFrom(const Math::Point3D& point) const override;
        void light(const HitObject& obj, Color& color, const Scene& scene) const override;
        ~PointLight() override = default;
    };
}
