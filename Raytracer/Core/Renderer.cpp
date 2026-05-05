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
        HitObject tempRec;
        bool hitAnything = false;
        double closest = infinity;
        for (const auto& object : scene.objects) {
            if (object->hit(ray, tempRec, epsilon, closest)) {
                hitAnything = true;
                closest = tempRec.t;
                obj = tempRec;
            }
        }
        if (!hitAnything)
            return {1, 1, 1}; // sky color
        Color direct = {0, 0, 0};
        scene.scene_lights.light(obj, direct, scene);
        Ray scatter;
        Color attenuation;
        if (obj.material->scatter(ray, obj, attenuation, scatter)) {
            Color indirect = attenuation * render(scatter, depth + 1);
            return direct + indirect;
        }
        return direct;
    }

    void Renderer::render_thread() {
        std::vector<std::pair<int, Color>> localResults;
        localResults.reserve((scene.cam.image_width * scene.cam.image_height) / number_of_threads + scene.cam.image_width * chunkSize);

        while (true) {
            int startY = row.fetch_add(chunkSize);
            if (startY >= scene.cam.image_height)
                break;
            int endY = std::min(startY + chunkSize, scene.cam.image_height);

            for (int y = startY; y < endY; ++y) {
                for (int x = 0; x < scene.cam.image_width; x++) {
                    Color pxl_color{0, 0, 0};
                    for (int i = 0; i < samples; i++) {
                        Ray r = scene.cam.ray(x, y);
                        pxl_color = pxl_color + render(r, 0);
                    }
                    pxl_color = pxl_color / samples;
                    int idx = x + (scene.cam.image_height - 1 - y) * scene.cam.image_width;
                    //helps with the speed of writes to buffer
                    localResults.emplace_back(idx, pxl_color);
                }
            }
        }
        for (auto& [idx, color] : localResults)
            print_Buffer[idx] = color;
    }

    void Renderer::setUpThreads(int num_of_threads) {
        std::vector<std::thread> threads;
        for (int i = 0; i < num_of_threads; i++) {
            threads.emplace_back(&Renderer::render_thread, this);
        }
        for (auto& t : threads) {
            t.join();
        }
    }

    void Renderer::render() {
        std::cout << "P3\n" << scene.cam.image_width << " " << scene.cam.image_height << "\n255\n";
        print_Buffer.resize(scene.cam.image_width * scene.cam.image_height);
        setUpThreads(number_of_threads);
        for(const auto &pxl : print_Buffer)
            writeColor(std::cout, pxl);
    };
}
