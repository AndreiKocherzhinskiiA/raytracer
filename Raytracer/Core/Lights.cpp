#include "Lights.hpp"
#include "HitObject.hpp"
#include "../Scene/Scene.hpp"
#include "../math/Ray.hpp"
#include "Constants.hpp"
#include <utility>
#include <iostream>


namespace RayTracer {
    void Lights::add(std::shared_ptr<ILight> newlight) {
        lights.push_back(std::move(newlight));
    }

    void Lights::light(const HitObject& obj, Color& color, const Scene& scene) const {
        HitObject rec;
        color = obj.material->color() * scene.ambient();
        for (const auto &light : lights) {
            Math::Vector3D lightDir = light->directionFrom(obj.point);
            double lightDist = light->maxDistanceFrom(obj.point);

            Ray shadowRay(obj.point + obj.normal * epsilon, lightDir);

            HitObject rec;
            bool blocked = false;
            for (const auto& object : scene.objects()) {
                if (object->hit(shadowRay, rec, 1e-6, lightDist)) {
                    blocked = true;
                    break;
                }
            }
            if (!blocked)
                light->light(obj, color, scene);
        }
    }
}