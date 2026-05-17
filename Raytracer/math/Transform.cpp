/*
** EPITECH PROJECT, 2026
** G-OOP-400-BAR-4-1-raytracer-7 [WSL: Ubuntu-24.04]
** File description:
** Transform
*/

#include "Transform.hpp"
#include <cmath>

namespace Math {
    double degreesToRadians(double degrees)
    {
        constexpr double PI = 3.14159265358979323846;

        return degrees * PI / 180.0;
    }

    Vector3D rotateX(const Vector3D &v, double angle)
    {
        double c = std::cos(angle);
        double s = std::sin(angle);

        return {v.x, v.y * c - v.z * s, v.y * s + v.z * c};
    }

    Vector3D rotateY(const Vector3D &v, double angle)
    {
        double c = std::cos(angle);
        double s = std::sin(angle);

        return {v.x * c + v.z * s, v.y, -v.x * s + v.z * c};
    }

    Vector3D rotateZ(const Vector3D &v, double angle)
    {
        double c = std::cos(angle);
        double s = std::sin(angle);

        return {v.x * c - v.y * s, v.x * s + v.y * c, v.z};
    }

    Vector3D rotateVector(const Vector3D &v, const Vector3D &rotation)
    {
        Vector3D radians(
            degreesToRadians(rotation.x),
            degreesToRadians(rotation.y),
            degreesToRadians(rotation.z)
        );

        return rotateZ(rotateY(rotateX(v, radians.x), radians.y), radians.z);
    }

    Vector3D inverseRotateVector(const Vector3D &v, const Vector3D &rotation)
    {
        Vector3D radians(
            degreesToRadians(rotation.x),
            degreesToRadians(rotation.y),
            degreesToRadians(rotation.z)
        );

        return rotateX(rotateY(rotateZ(v, -radians.z), -radians.y), -radians.x);
    }
}
