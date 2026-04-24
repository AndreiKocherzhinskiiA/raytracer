#pragma once

#include "../Scene/Camera.hpp"
#include "../Scene/Scene.hpp"
#include "../Core/HittableList.hpp"
#include "../Core/IObject.hpp"
#include "../Core/ILight.hpp"

#include "iostream"
#include <limits>

namespace RayTracer {
    inline constexpr double epsilon = 1e-8;
    inline constexpr double infinity = std::numeric_limits<double>::infinity();
    class Renderer
    {
    private:
        void writeColor(std::ostream& out, const Color& pixel_color);
        const Scene &scene;
        int max_depth = 3;
    public:
        ~Renderer() = default;
        Renderer(const Scene &scene);
        void render();
        Color render(const Ray &ray, int depth = 0);
    };
}

// std::cout << cam.image_width << " " << cam.image_height << "\n255\n";
// HitObject hit_x;
// for (int y = cam.image_height - 1; y >= 0 ; y--) {
//     for (int x = 0; x < cam.image_width ; x++) {
//         Color pixel(0, 0, 0);
//         Ray r = cam.ray(x, y);
//         if (scene.hit(r, 0.001, INFINITY, hit_x)) {
//             Math::Vector3D n = (hit_x.normal + Math::Vector3D(1, 1, 1)) * 0.5;
//             Color pixel(n.x, n.y, n.z);
//             writeColor(std::cout, pixel);
//         } else {
//             writeColor(std::cout, pixel);
//         }
//     }
// }
