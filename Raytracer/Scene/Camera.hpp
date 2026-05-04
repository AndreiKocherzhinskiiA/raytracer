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

    Camera(int width, int height, const Math::Point3D &origin, double fov)
        : image_width(width), image_height(height),
          field_of_view(fov), origin(origin)
    {
        makeScreen();
    }

    void makeScreen()
    {
        constexpr double PI = 3.14159265358979323846;

        double aspect = static_cast<double>(image_width) / image_height;
        double vp_h = 2.0 * std::tan(field_of_view * PI / 360.0);
        double vp_w = vp_h * aspect;

        double pitch = rotation.x * PI / 180.0;
        double yaw = rotation.y * PI / 180.0;
        double roll = rotation.z * PI / 180.0;

        Math::Vector3D fwd = {
            std::sin(yaw) * std::cos(pitch),
            std::sin(pitch),
            -std::cos(yaw) * std::cos(pitch)
        };

        const Math::Vector3D worldUp = {0.0, 1.0, 0.0};
        const Math::Vector3D worldForward = {0.0, 0.0, -1.0};

        Math::Vector3D right, up;
        if (std::abs(fwd.dot(worldUp)) > 0.999) {
            right = worldUp.cross(worldForward).normalize();
        } else {
            right = worldUp.cross(fwd).normalize();
        }
        up = fwd.cross(right).normalize();

        if (roll != 0.0) {
            double cr = std::cos(roll);
            double sr = std::sin(roll);
            Math::Vector3D rolledRight = right * cr + up * sr;
            Math::Vector3D rolledUp = right * (-sr) + up * cr;
            right = rolledRight;
            up = rolledUp;
        }

        Math::Point3D vpCenter = origin + fwd;

        screen.origin = vpCenter + right * (-vp_w / 2.0) + up * (-vp_h / 2.0);
        screen.u_axis = right * vp_w;
        screen.v_axis = up * vp_h;
    }

    Ray ray(int x, int y) const
    {
        double u = (x + Math::Vector3D::randomDouble(0.0, 1.0)) / image_width;
        double v = (y + Math::Vector3D::randomDouble(0.0, 1.0)) / image_height;
        Math::Point3D pixel = screen.pointAt(u, v);
        Math::Vector3D direction = (pixel - origin).normalize();

        return Ray(origin, direction);
    }

    void setOrigin(const Math::Point3D &o) { origin = o; makeScreen(); }
    void setRotation(const Math::Vector3D &r) { rotation = r; makeScreen(); }
    void setFov(double fov) { field_of_view = fov; makeScreen(); }
    void setResolution(int w, int h) { image_width = w; image_height = h; makeScreen(); }
};

} // namespace RayTracer