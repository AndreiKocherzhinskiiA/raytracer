#pragma once
#include "../math/Ray.hpp"
#include "../Scene/Scene.hpp"
#include "HitObject.hpp"
#include "Color.hpp"
class HitObject;

namespace RayTracer {
    class ILights
    {
    private:
        /* data */
    public:
        virtual void light(const HitObject& obj, Color& color, const Scene& scene) = 0;
        ~ILights() = default;
    };
}
