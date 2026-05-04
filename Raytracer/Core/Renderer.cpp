#include "Renderer.hpp"
#include "../Core/HitObject.hpp"
#include <algorithm>

namespace RayTracer {
    Renderer::Renderer(const Scene &scene) : scene(scene) {};

    void Renderer::writeColor(std::ostream& out, const Color& pixel_color) {
        auto r = pixel_color.r;
        auto g = pixel_color.g;
        auto b = pixel_color.b;
        // std::clog << "r=" << r << " g=" << g << " b=" << b << std::endl;

        r = std::clamp(r, 0.0, 1.0);
        g = std::clamp(g, 0.0, 1.0);
        b = std::clamp(b, 0.0, 1.0);
        //helps with brightness
        // r = std::pow(r, 1.0 / 2.2);
        // g = std::pow(g, 1.0 / 2.2);
        // b = std::pow(b, 1.0 / 2.2);

        int rbyte = int(255.999 * r);
        int gbyte = int(255.999 * g);
        int bbyte = int(255.999 * b);
        out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
    };


    Color Renderer::render(const Ray &ray, int depth) {
        if (depth >= max_depth)
            return {0, 0, 0};

        HitObject obj;
        if (!scene.hittable_list.hit(ray, obj, epsilon, infinity)) {
            return {1, 1, 1};; //sky color
        }
        Color direct = {0, 0, 0};
        scene.scene_lights.light(obj, direct, scene);
        // std::cerr << "after light: " << color.r << " " << color.g << " " << color.b << "\n";
        Ray scatter;
        Color attenuation;
        if (obj.material->scatter(ray, obj, attenuation, scatter)) {
            Color indirect = attenuation * render(scatter, depth + 1);
            return direct + indirect;
        }
        return direct;
    };

    
    void Renderer::render() {
        Color pxl_color;
        int samples = 100;
        std::cout << "P3\n" << scene.cam.image_width << " " << scene.cam.image_height << "\n255\n";
        std::vector<Color> print_Buffer(scene.cam.image_width * scene.cam.image_height);
        for (int y = scene.cam.image_height - 1; y >= 0 ; y--) {
            for (int x = 0; x < scene.cam.image_width ; x++) {
                for (int i = 0; i < samples; i++) {
                    Ray r = scene.cam.ray(x, y);
                    pxl_color = pxl_color + render(r, 0);
                }
                pxl_color = pxl_color / samples;
                print_Buffer[x + (scene.cam.image_height - 1 - y) * scene.cam.image_width] = pxl_color;
            }
        }
        for(const auto &pxl : print_Buffer)
            writeColor(std::cout, pxl);
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
