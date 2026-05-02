#pragma once
#include "../math/Ray.hpp"
#include "Rectangle3D.hpp"
#include <cmath>

namespace RayTracer {

class Camera {
public:
    int image_width = 1920;
    int image_height = 1080;
    double field_of_view = 72.0;
    Math::Point3D origin = {0, 0, 0};
    Math::Vector3D rotation = {0, 0, 0};
    Rectangle3D screen;

    Camera() = default;

    Camera(int width, int height, const Math::Point3D &origin, float fov)
    : image_width(width), image_height(height), field_of_view(fov), origin(origin)
    {
        makeScreen();
    }

    void makeScreen()
    {
        constexpr double PI = 3.14159265358979323846;

        double aspect = static_cast<double>(image_width) / image_height;
        double scale = std::tan(field_of_view * PI / 360.0);
        double vp_h = 2.0 * scale;
        double vp_w = vp_h * aspect;

        double pitch = rotation.x * PI / 180.0;
        double yaw = rotation.y * PI / 180.0;

        Math::Vector3D fwd = { std::sin(yaw) * std::cos(pitch), std::sin(pitch), -std::cos(yaw) * std::cos(pitch) };
        Math::Vector3D right = Math::Vector3D(0, 1, 0).cross(fwd).normalize();
        Math::Vector3D up = fwd.cross(right).normalize();

        Math::Point3D center = origin + fwd;
        screen.origin = center - right * (vp_w / 2.0) + up * (vp_h / 2.0);
        screen.bottom_side = right * vp_w;
        screen.left_side = up * -vp_h;
    }

    Ray ray(int x, int y) const
    {
        double u = (x + 0.5) / image_width;
        double v = (y + 0.5) / image_height;
        Math::Point3D  pixel = screen.pointAt(u, v);
        Math::Vector3D direction = (pixel - origin).normalize();
        return Ray(origin, direction);
    }
};

} // namespace RayTracer