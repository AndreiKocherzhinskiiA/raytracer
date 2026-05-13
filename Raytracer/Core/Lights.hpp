#pragma once
#include "ILight.hpp"
#include <memory>
#include <vector>

namespace RayTracer {
    class HitObject;
    class Scene;

    class Lights
    {
    private:
        std::vector<std::shared_ptr<ILight>> lights;

    public:
        Lights() = default;
        void add(std::shared_ptr<ILight> newlight);
        void light(const HitObject& obj, Color& color, const Scene& scene) const;
        ~Lights() = default;
    };
}