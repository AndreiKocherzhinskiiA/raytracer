#include "Ray.hpp"
#include "Rectangle3D.hpp"
#include "Camera.hpp"
#include "Sphere.hpp"
#include <iostream>
#include <string>
#include "Color.hpp"

void write_color(std::ostream& out, const Color& pixel_color) {
    auto r = pixel_color.r;
    auto g = pixel_color.g;
    auto b = pixel_color.b;
    // std::clog << "r=" << r << " g=" << g << " b=" << b << std::endl;
    // Translate the [0,1] component values to the byte range [0,255].
    int rbyte = int(255.999 * r);
    int gbyte = int(255.999 * g);
    int bbyte = int(255.999 * b);

    // Write out the pixel color components.
    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

Color ray_color(const RayTracer::Ray& r) {
    static RayTracer::Sphere s(Math::Point3D(0.5, 0, -1), 0.7);
    double t = s.hit(r);

    if (t > 0.0) {
        Math::Vector3D N = (r.at(t) - Math::Point3D(0, 0, -1)).normalize();
        return 0.5 * Color(N.x + 1, N.y + 1, N.z + 1);
    }
    Math::Vector3D unit_direction = r.direction.normalize();
    auto a = 0.5 * (unit_direction.y + 1.0);
    return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
}



int main()
{
    const int image_width  = 800;
    const int image_height = 600;

    std::cout << "P3\n";
    std::cout << image_width << " " << image_height << "\n";
    std::cout << "255\n";

    RayTracer::Camera cam;

    for (int y = 0; y < image_height; y++) {
        for (int x = 0; x < image_width; x++) {
            double u = (double)x / (image_width - 1);
            double v = (double)y / (image_height - 1);

            RayTracer::Ray r = cam.ray(u, v);
            write_color(std::cout, ray_color(r));
        }
    }
}