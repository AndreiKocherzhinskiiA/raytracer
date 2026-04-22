#pragma once

class Color
{
private:
public:
    double r;
    double g;
    double b;
    Color(/* args */) = default;
    Color(double r, double g, double b): r(r), g(g), b(b) {};
    Color operator+(const Color& other) const {
        return Color(r + other.r, g + other.g, b + other.b);
    }
    Color operator*(double t) const {
        return Color(r * t, g * t, b * t);
    }
    Color operator*(const Color& other) const {
        return Color(r * other.r, g * other.g, b * other.b);
    }
    friend Color operator*(double t, const Color& c) {
        return c * t;
    }

    ~Color() = default;
};