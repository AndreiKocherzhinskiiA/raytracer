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
    // //Camera(const std::string& file_path) 
    // {
    //     libconfig::Config cfg;
    //     cfg.readFile(file_path);

    //     cfg.lookupValue("camera.resolution.width", image_width);
    //     cfg.lookupValue("camera.resolution.height", image_height);

    //     cfg.lookupValue("camera.position.x", origin.x);
    //     cfg.lookupValue("camera.position.y", origin.y);
    //     cfg.lookupValue("camera.position.z", origin.z);

    //     cfg.lookupValue("camera.rotation.x", rotation.x);
    //     cfg.lookupValue("camera.rotation.y", rotation.y);
    //     cfg.lookupValue("camera.rotation.z", rotation.z);

    //     cfg.lookupValue("camera.fieldOfView", field_of_view);
    //     makeScreen();
    //     std::cout << "setup cam" << std::endl;
    // }
    Camera(Math::Point3D origin, Rectangle3D screen)
        : origin(origin), screen(screen) {}

    void makeScreen() {
        //double aspect = image_height * 1 / image_width;
        double aspect = (double)image_width / (double)image_height;
        double height = 2 * tan(field_of_view * M_PI / 360.0);
        double width = height * aspect;

        screen.origin = {origin.x - width / 2, origin.y + height / 2, origin.z - 1};
        screen.bottom_side = {width, 0, 0};
        screen.left_side = {0, -height, 0};
    }

    Ray ray(double u, double v) const {
        Math::Point3D pixel = screen.pointAt(u, v);
        Math::Vector3D direction = (pixel - origin).normalize();
        return Ray(origin, direction);
    }

    ~Camera() = default;
};

} // namespace RayTracer