#include "Point.hpp"
#include "../Core/HitObject.hpp"
#include "../Scene/Scene.hpp"
#include <algorithm>
#include <algorithm>

namespace RayTracer {
    PointLight::PointLight(Math::Point3D pos, Color color)
        : _pos(pos), _color(color) {}

    Math::Vector3D PointLight::directionFrom(const Math::Point3D& point) const {
        return (_pos - point).normalize();
    }

    double PointLight::maxDistanceFrom(const Math::Point3D& point) const {
        return (_pos - point).length();
    }

    void PointLight::light(const HitObject& obj, Color& color, const Scene& scene) const {
        Math::Vector3D lightDir = directionFrom(obj.point);
        double diff = std::max(0.0, obj.normal.dot(lightDir));
        // double dist = (_pos - obj.point).length();
        // double att = 1.0 / (1.0 + 0.005 * dist * dist);
        color = color + (_color * diff * scene.diffuse);
    }
}