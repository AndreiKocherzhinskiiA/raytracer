#include "FlatColor.hpp"
#include "../Core/HitObject.hpp"


namespace RayTracer {
        FlatColor::FlatColor(const Color c): _color(c){};
        FlatColor::FlatColor(const libconfig::Setting& s) {

            const auto &c = s["color"];
            double r = 255, g = 255, b = 255;

            if(s.exists("color")) {
                c.lookupValue("r", r);
                c.lookupValue("g", g);
                c.lookupValue("b", b);
            }
            _color = Color(r / 255.0, g / 255.0, b / 255.0);

        }
        bool FlatColor::scatter(const Ray& rayIn, const HitObject& rec, Color& color, Ray& scattered) const {
            (void)rayIn;
            (void)rec;
            (void)color;
            (void)scattered;
            return false; // was true
        };
        const Color &FlatColor::color() const {
            return _color;
        }
        // FlatColor::~FlatColor() = default;
};

