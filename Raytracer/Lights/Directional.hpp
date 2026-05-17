#pragma once
#include "../Core/ILight.hpp"
#include <libconfig.h++>

namespace RayTracer {
    class Directional : public ILight {
    private:
        Math::Vector3D _dir;
        Color _color;

    public:
        Directional(const libconfig::Setting& s);
        Math::Vector3D directionFrom(const Math::Point3D& point) const override;
        double maxDistanceFrom(const Math::Point3D& point) const override;
        void light(const HitObject& obj, Color& color, const Scene& scene) const override;
        ~Directional() override = default;
    };

}
