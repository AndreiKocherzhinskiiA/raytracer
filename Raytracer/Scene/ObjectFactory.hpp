#pragma once

#include "../Core/IObject.hpp"
#include <functional>
#include <string>
#include <unordered_map>
#include "../Core/HittableList.hpp"
#include "../Primitives/Sphere.hpp"
#include "../Primitives/Plane.hpp"

// #include 

//NEED TO GET SHAPE FROM coning file.

namespace RayTracer {

class ObjectFactory {
// private:
//     using FactoryFunc = std::function<std::shared_ptr<RayTracer::IObject>(const std::string &)>;
//     static std::unordered_map<std::string, FactoryFunc> _funcMap;
public:
    static std::shared_ptr<IObject> createSphere(
        const Math::Point3D &center,
        double radius,
        const Color &color
    );
    static std::shared_ptr<IObject> createPlane(
        Axis axis,
        double position,
        const Color &color
    );
};
    // std::shared_ptr<RayTracer::IObject> makeObject(const std::string &path, const RayTracer::HittableList & list);
    // ObjectFactory(/* args */);
    // ~ObjectFactory();
}