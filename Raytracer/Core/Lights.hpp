#pragma once
#include "ILight.hpp"
#include "../Core/HittableList.hpp"
#include "../Core/IObject.hpp"
#include "../Scene/Scene.hpp"

namespace RayTracer {
    inline constexpr double epsilon = 1e-8;
    inline constexpr double infinity = std::numeric_limits<double>::infinity();
    class Lights
    {
    private:
        std::vector<std::unique_ptr<ILight>> lights;
    public:
        Lights()= default;
        void add(std::unique_ptr<ILight> newlight) {
            lights.push_back(newlight);
        }
        void light(const HitObject& obj, Color& color, const Scene& scene) const{
            HitObject rec;
            for (const auto &light: lights) {
                Math::Vector3D toLight = light->position() - obj.point;
                double lightDist = toLight.length();
                Math::Vector3D lightDir = toLight / lightDist;
                Ray shadowRay(obj.point + obj.normal * epsilon, lightDir);
                if (!scene.hittable_list.hit(shadowRay, rec, epsilon, infinity)) {
                    light->light(obj, color, scene);
                }
            }
        };
        ~Lights();
    };
}