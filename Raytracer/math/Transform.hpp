/*
** EPITECH PROJECT, 2026
** G-OOP-400-BAR-4-1-raytracer-7 [WSL: Ubuntu-24.04]
** File description:
** Transform
*/

#pragma once

#include "Vector3D.hpp"

namespace Math {
    double degreesToRadians(double degrees);
    Vector3D rotateX(const Vector3D &v, double angle);
    Vector3D rotateY(const Vector3D &v, double angle);
    Vector3D rotateZ(const Vector3D &v, double angle);
    Vector3D rotateVector(const Vector3D &v, const Vector3D &rotation);
    Vector3D inverseRotateVector(const Vector3D &v, const Vector3D &rotation);
}
