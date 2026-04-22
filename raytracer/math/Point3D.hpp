#pragma once

#include <cmath>
#include "Vector3D.hpp"

namespace Math
{
    class Point3D
    {
    private:
        /* data */
    public:
        double x;
        double y;
        double z;

        Point3D() = default;
        Point3D(double x, double y, double z): x(x), y(y), z(z) {};
        double length() const {
            return std::sqrt(x * x + y * y + z * z);
        }
        double dot(const Point3D& other) const {
            return x * other.x + y * other.y + z * other.z;
        }

        Math::Point3D operator-(const Math::Vector3D& v) const {
            return Math::Point3D(x - v.x, y - v.y, z - v.z);
        }

        Point3D operator+(const Vector3D& v)const {
            Point3D newP;
            newP.x = x + v.x;
            newP.y = y + v.y;
            newP.z = z + v.z;
            return newP;
        }
        Point3D& operator+=(const Vector3D& v) {
            x += v.x;
            y += v.y;
            z += v.z;
            return *this;
        }

        Vector3D operator-(const Point3D& other) const {
            return {x - other.x, y - other.y, z - other.z};
        }

        ~Point3D()= default;
    };

} // namespace Math
