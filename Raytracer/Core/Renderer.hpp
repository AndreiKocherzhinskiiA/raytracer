#pragma once

#include "../Scene/Camera.hpp"
#include "../Scene/Scene.hpp"
#include "../Core/HittableList.hpp"
#include "../Core/HitObject.hpp"
#include "../Core/IObject.hpp"
#include "../Core/ILight.hpp"
#include "Constants.hpp"
#include <vector>
#include <thread>
#include <mutex>
#include <atomic>

#include "iostream"
// #include <limits>'


namespace RayTracer {
    class Renderer
    {
    private:
        void writeColor(std::ostream& out, const Color& pixel_color);
        const Scene &scene;
        int max_depth = 3;
        void setUpThreads(int num_of_threads);
        std::vector<Color> print_Buffer;
        std::atomic<int> row = 0;
        void renderRow(int y);
        const int number_of_threads = 8;
        const int samples = 100;
        const int chunkSize = 128;
    public:
        void render_thread();
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
