#include "Renderer.hpp"
namespace RayTracer {
    Renderer::Renderer(const Scene &scene) : scene(scene) {};

    void Renderer::writeColor(std::ostream& out, const Color& pixel_color) {
        auto r = pixel_color.r;
        auto g = pixel_color.g;
        auto b = pixel_color.b;
        // std::clog << "r=" << r << " g=" << g << " b=" << b << std::endl;
        int rbyte = int(1 * r); //255.999
        int gbyte = int(1 * g);
        int bbyte = int(1 * b);
        out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
    };


    Color Renderer::render(const Ray &ray, int depth) {
        if (depth >= max_depth)
            return {0, 0, 0};

        HitObject obj;
        if (!scene.hittable_list.hit(ray, obj, epsilon, infinity)) {
            return {1, 1, 1};; //sky color
        }
        Color color;
        // scene.lights.light(obj, color, scene);
        Ray scatter;
        if (obj.material->scatter(ray, obj, color, scatter)) {
            return color * render(scatter, depth + 1);
        }
        return obj.material->color();
    };

    
    void Renderer::render() {
        Color color;
        std::cout << "P3\n" << scene.cam.image_width << " " << scene.cam.image_height << "\n255\n";
        for (int y = scene.cam.image_height - 1; y >= 0 ; y--) {
            for (int x = 0; x < scene.cam.image_width ; x++) {
                Ray r = scene.cam.ray(x, y);
                color = render(r, 0);
                writeColor(std::cout, color);
            }
        }
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
