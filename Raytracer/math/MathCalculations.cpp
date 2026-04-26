/*
** EPITECH PROJECT, 2026
** G-OOP-400-BAR-4-1-raytracer-7 [WSL: Ubuntu-24.04]
** File description:
** MathCalculations
*/


#include "MathCalculations.hpp"
#include <cmath>
#include <limits>

namespace Math::Calc {
    double degreesToRadians(double degrees)
    {
      constexpr double kPi = 3.14159265358979323846;

        return degrees * kPi / 180.0;
    }

    Math::Vector3D normalize(const Math::Vector3D &v)
    {
        const double len = v.length();
        if (len <= kEpsilon) {
            return {0.0, 0.0, 0.0};
        }
        return v / len;
    }

    double clamp(double value, double min, double max)
    {
        if (value < min) {
            return min;
        }
        if (value > max) {
            return max;
        }
        return value;
    }

    HitResult nearestRoot(double rootA, double rootB, double tMin, double tMax)
    {
        double nearest = std::numeric_limits<double>::infinity();

        if (rootA >= tMin && rootA <= tMax) {
            nearest = rootA;
        }
        if (rootB >= tMin && rootB <= tMax && rootB < nearest) {
            nearest = rootB;
        }
        if (!std::isfinite(nearest)) {
            return {false, -1.0};
        }
        return {true, nearest};
    }

    std::pair<double, double> pixelToNormalized(int x, int y, int width, int height)
    {
        const double u = (static_cast<double>(x) + 0.5) / static_cast<double>(width);
        const double v = (static_cast<double>(y) + 0.5) / static_cast<double>(height);

        return {u, v};
    }

    std::pair<double, double> normalizedToScreen(double u, double v, double aspect, double fovRadians)
    {
        const double halfTan = std::tan(fovRadians / 2.0);
        const double xScreen = (2.0 * u - 1.0) * aspect * halfTan;
        const double yScreen = (1.0 - 2.0 * v) * halfTan;

        return {xScreen, yScreen};
    }

    Math::Vector3D buildRayDirection(
        double screenX,
        double screenY,
        const Math::Vector3D &right,
        const Math::Vector3D &up,
        const Math::Vector3D &forward
    )
    {
        const Math::Vector3D rawDirection = right * screenX + up * screenY + forward;

        return normalize(rawDirection);
    }

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
    )
    {
        const auto uv = pixelToNormalized(x, y, width, height);
        const double aspect = static_cast<double>(width) / static_cast<double>(height);
        const auto screen = normalizedToScreen(uv.first, uv.second, aspect, fovRadians);
        const Math::Vector3D direction = buildRayDirection(screen.first, screen.second, right, up, forward);

        return {origin, direction};
    }

    Math::Point3D pointAt(const RayTracer::Ray &ray, double t)
    {
        return ray.origin + ray.direction * t;
    }

    HitResult intersectPlane(
        const RayTracer::Ray &ray,
        const Math::Point3D &planePoint,
        const Math::Vector3D &planeNormal
    )
    {
        const Math::Vector3D normalizedPlaneNormal = normalize(planeNormal);
        const double denominator = ray.direction.dot(normalizedPlaneNormal);

        if (std::fabs(denominator) <= kEpsilon) {
            return {false, -1.0};
        }

        const Math::Vector3D p0l0 = planePoint - ray.origin;
        const double t = p0l0.dot(normalizedPlaneNormal) / denominator;
        if (t <= kEpsilon) {
            return {false, -1.0};
        }
        return {true, t};
    }

    Math::Vector3D planeNormal(const Math::Vector3D &n)
    {
        return normalize(n);
    }

    Math::Vector3D directionalLightVector(const Math::Vector3D &lightDirection)
    {
        return normalize(lightDirection * -1.0);
    }

    Math::Vector3D pointLightVector(const Math::Point3D &lightPosition, const Math::Point3D &surfacePoint)
    {
        return normalize(lightPosition - surfacePoint);
    }

    double diffuseLambert(double kd, const Math::Vector3D &n, const Math::Vector3D &l)
    {
        const double nDotL = normalize(n).dot(normalize(l));

        return kd * std::max(0.0, nDotL);
    }

    Lighting lighting(double ka, double kd, const Math::Vector3D &n, const Math::Vector3D &l)
    {
        return {ka, diffuseLambert(kd, n, l)};
    }

    Math::Vector3D shade(
        const Math::Vector3D &objectColor,
        double ka,
        double kd,
        const Math::Vector3D &n,
        const Math::Vector3D &l
    )
    {
        const Lighting lit = lighting(ka, kd, n, l);
        const double intensity = clamp(lit.ambient + lit.diffuse, 0.0, 1.0);

        return objectColor * intensity;
    }

    RayTracer::Ray buildShadowRay(
        const Math::Point3D &surfacePoint,
        const Math::Vector3D &normal,
        const Math::Vector3D &lightVector,
        double epsilon
    )
    {
        const Math::Point3D offsetOrigin = surfacePoint + normalize(normal) * epsilon;

        return {offsetOrigin, normalize(lightVector)};
    }
}
