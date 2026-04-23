#pragma once

#include "../Scene/Camera.hpp"
#include "../Core/HittableList.hpp"
#include "iostream"

namespace RayTracer {

    class Render
    {
    private:
        void writeColor(std::ostream& out, const Color& pixel_color) {
            auto r = pixel_color.r;
            auto g = pixel_color.g;
            auto b = pixel_color.b;
            // std::clog << "r=" << r << " g=" << g << " b=" << b << std::endl;
            int rbyte = int(255.999 * r);
            int gbyte = int(255.999 * g);
            int bbyte = int(255.999 * b);
            out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
        };
    public:
        // Render(/* args */) = default;
        ~Render() = default;
        Render(const HittableList& scene, const Camera& cam) {
            std::cout << cam.image_width << " " << cam.image_height << "\n255\n";
            HitObject hit_x;
            for (int y = cam.image_height - 1; y >= 0 ; y--) {
                for (int x = 0; x < cam.image_width ; x++) {
                    Color pixel(0, 0, 0);
                    Ray r = cam.ray(x, y);
                    if (scene.hit(r, 0.001, INFINITY, hit_x)) {
                        Math::Vector3D n = (hit_x.normal + Math::Vector3D(1, 1, 1)) * 0.5;
                        Color pixel(n.x, n.y, n.z);
                        writeColor(std::cout, pixel);
                    } else {
                        writeColor(std::cout, pixel);
                    }
                }
            }
        };
    };

}
