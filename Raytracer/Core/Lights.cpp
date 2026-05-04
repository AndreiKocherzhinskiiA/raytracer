#include "Lights.hpp"
#include "HitObject.hpp"
#include "../Scene/Scene.hpp"
#include "../math/Ray.hpp"
#include "Constants.hpp"
#include <utility>
#include <iostream>


namespace RayTracer {
    void Lights::add(std::unique_ptr<ILight> newlight) {
        lights.push_back(std::move(newlight));
    }

    void Lights::light(const HitObject& obj, Color& color, const Scene& scene) const {
        HitObject rec;
        color = obj.material->color() * scene.ambient;
        for (const auto &light : lights) {
            Math::Vector3D lightDir = light->directionFrom(obj.point);
            double lightDist = light->maxDistanceFrom(obj.point);

            Ray shadowRay(obj.point + obj.normal * epsilon, lightDir);

            if (!scene.hittable_list.hit(shadowRay, rec, epsilon, lightDist)) {
                light->light(obj, color, scene);
            }
        }
    }
}