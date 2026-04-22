#pragma once

#include <cmath>

namespace Math
{
    class Vector3D
    {
    private:
        /* data */
    public:
        double x;
        double y;
        double z;

        Vector3D()= default;
        Vector3D(double x, double y, double z): x(x), y(y), z(z) {};
        double lengthSquared() const {
            return x * x + y * y + z * z;
        }
        double length() const {
            return std::sqrt(x * x + y * y + z * z);
        }
        double dot(const Vector3D& other) const {
            return x * other.x + y * other.y + z * other.z;
        }
        Vector3D normalize() const {
            double len = length();
            if (len == 0.0) return *this;
            return *this / len;
        }

        Vector3D operator+(const Vector3D &other) const{
            Vector3D newV;
            newV.x = x + other.x;
            newV.y = y + other.y;
            newV.z = z + other.z;
            return newV;
        }

        Vector3D operator-(const Vector3D &other)const {
            Vector3D newV;
            newV.x = x - other.x;
            newV.y = y - other.y;
            newV.z = z - other.z;
            return newV;
        }

        Vector3D operator*(const Vector3D &other)const {
            Vector3D newV;
            newV.x = x * other.x;
            newV.y = y * other.y;
            newV.z = z * other.z;
            return newV;
        }

        Vector3D operator/(const Vector3D &other)const {
            Vector3D newV;
            newV.x = x / other.x;
            newV.y = y / other.y;
            newV.z = z / other.z;
            return newV;
        }

        Vector3D &operator+=(const Vector3D &other) {
            x += other.x;
            y += other.y;
            z += other.z;
            return *this;
        }

        Vector3D operator-=(const Vector3D &other) {
            x -= other.x;
            y -= other.y;
            z -= other.z;
            return *this;
        }

        Vector3D operator*=(const Vector3D &other) {
            x *= other.x;
            y *= other.y;
            z *= other.z;
            return *this;
        }

        Vector3D operator/=(const Vector3D &other) {
            x += other.x;
            y += other.y;
            z += other.z;
            return *this;
        }

        //

        Vector3D operator*(double d) const{
            Vector3D newV;
            newV.x = x * d;
            newV.y = y * d;
            newV.z = z * d;
            return newV;
        }

        Vector3D operator/(double d)const {
            Vector3D newV;
            newV.x = x / d;
            newV.y = y / d;
            newV.z = z / d;
            return newV;
        }
        Vector3D operator*=(double d) {
            x *= d;
            y *= d;
            z *= d;
            return *this;
        }

        Vector3D operator/=(double d) {
            x += d;
            y += d;
            z += d;
            return *this;
        }

        ~Vector3D()= default;
    };

} // namespace Math
