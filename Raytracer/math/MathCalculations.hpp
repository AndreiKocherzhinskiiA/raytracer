/*
** EPITECH PROJECT, 2026
** G-OOP-400-BAR-4-1-raytracer-7 [WSL: Ubuntu-24.04]
** File description:
** MathCalculations
*/

#pragma once

#include <utility>
#include "Ray.hpp"

namespace Math::Calc {
    inline constexpr double kEpsilon = 1e-6;

    struct HitResult {
        bool hit;
        double t;
    };

    struct Lighting {
        double ambient;
        double diffuse;
    };

    double degreesToRadians(double degrees);
    Math::Vector3D normalize(const Math::Vector3D &v);
    double clamp(double value, double min, double max);
    HitResult nearestRoot(double rootA, double rootB, double tMin, double tMax);

    std::pair<double, double> pixelToNormalized(int x, int y, int width, int height);
    std::pair<double, double> normalizedToScreen(double u, double v, double aspect, double fovRadians);

    Math::Vector3D buildRayDirection(
        double screenX,
        double screenY,
        const Math::Vector3D &right,
        const Math::Vector3D &up,
        const Math::Vector3D &forward
    );

    RayTracer::Ray buildPrimaryRay(
        const Math::Point3D &origin,
        int x,
        int y,
        int width,
        int height,
        double fovRadians,
        const Math::Vector3D &right,
        const Math::Vector3D &up,
        const Math::Vector3D &forward
    );

    Math::Point3D pointAt(const RayTracer::Ray &ray, double t);
    HitResult intersectSphere(
        const RayTracer::Ray &ray,
        const Math::Point3D &center,
        double radius,
        double tMin,
        double tMax
    );
    HitResult intersectPlane(
        const RayTracer::Ray &ray,
        const Math::Point3D &planePoint,
        const Math::Vector3D &planeNormal
    );

    Math::Vector3D planeNormal(const Math::Vector3D &n);

    Math::Vector3D directionalLightVector(const Math::Vector3D &lightDirection);
    Math::Vector3D pointLightVector(const Math::Point3D &lightPosition, const Math::Point3D &surfacePoint);

    double diffuseLambert(double kd, const Math::Vector3D &n, const Math::Vector3D &l);
    Lighting lighting(double ka, double kd, const Math::Vector3D &n, const Math::Vector3D &l);

    Math::Vector3D shade(
        const Math::Vector3D &objectColor,
        double ka,
        double kd,
        const Math::Vector3D &n,
        const Math::Vector3D &l
    );

    RayTracer::Ray buildShadowRay(
        const Math::Point3D &surfacePoint,
        const Math::Vector3D &normal,
        const Math::Vector3D &lightVector,
        double epsilon = kEpsilon
    );
}
