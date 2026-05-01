#pragma once

#include "../math/Ray.hpp"
#include "Rectangle3D.hpp"
#include <string>
#include <iostream>

namespace RayTracer {

class Camera {
public:
    int image_width = 1920;
    int image_height = 1080;
    float field_of_view = 72.0f;
    Math::Point3D origin = {0, 0, 0};
    Math::Point3D rotation = {0, 0, 0};
    Rectangle3D screen;

    Camera() = default;

    Camera(int width, int height, const Math::Point3D &origin, float fov)
    {
        this->image_width = width;
        this->image_height = height;
        this->origin = origin;
        this->field_of_view= fov;
        makeScreen();
    }

    Camera(Math::Point3D origin, Rectangle3D screen)
        : origin(origin), screen(screen) {}

        void makeScreen() {
            double aspect = (double)image_width / (double)image_height;
            double theta = field_of_view * M_PI / 180.0;  // Degrees → radians
            double height = 2 * tan(theta / 2.0);         // ← This line
            double width = height * aspect;
        
            double focal = height / tan(theta / 2.0);     // Focal length
        
            screen.origin = {
                origin.x - width / 2.0,
                origin.y + height / 2.0,
                origin.z - focal                          // ← Key fix
            };
            screen.bottom_side = {width, 0, 0};
            screen.left_side = {0, -height, 0};
        }

    Ray ray(int x, int y) const {
        // std::cout << "[CAMERA DEBUG] screen.origin.z=" << screen.origin.z << std::endl;
        double u = (x + 0.5) / image_width;
        double v = (y + 0.5) / image_height;
        Math::Point3D pixel = screen.pointAt(u, v);
        Math::Vector3D direction = (pixel - origin).normalize();
        return Ray(origin, direction);
    }

    ~Camera() = default;
};

} // namespace RayTracer