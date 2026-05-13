#include "Directional.hpp"
#include "../Core/HitObject.hpp"
#include "../Scene/Scene.hpp"
#include "../Core/Constants.hpp"
#include <algorithm>

namespace RayTracer {

    Directional::Directional(Math::Vector3D dir, Color color)
        : _dir(dir.normalize()), _color(color) {}

    Math::Vector3D Directional::directionFrom(const Math::Point3D& point) const {
        (void)point;
        return Math::Vector3D(-_dir.x, -_dir.y, -_dir.z);
    }

    double Directional::maxDistanceFrom(const Math::Point3D& point) const {
        (void)point;
        return infinity;
    }

    void Directional::light(const HitObject& obj, Color& color, const Scene& scene) const {
        Math::Vector3D lightDir = directionFrom(obj.point).normalize();
        double diff = std::max(0.0, obj.normal.dot(lightDir));
        color = color + (obj.material->color() * _color * diff * scene.diffuse());
    }

}