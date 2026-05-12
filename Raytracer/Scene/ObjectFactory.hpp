#pragma once

#include "../Core/IObject.hpp"
#include <functional>
#include <string>
#include <unordered_map>
#include <vector>
#include "../Primitives/Sphere.hpp"
#include "../Primitives/Plane.hpp"
#include "../Primitives/Cylinder.hpp"
#include "../Primitives/Cone.hpp"
#include "../Primitives/Cube.hpp"

// #include 

//NEED TO GET SHAPE FROM coning file.

namespace RayTracer {

class ObjectFactory {
private:
    using FactoryFunc = std::function<std::shared_ptr<RayTracer::IObject>(const libconfig::Setting &)>;
    static const std::unordered_map<std::string, FactoryFunc> &funcMap();

public:
    static bool hasType(const std::string &type);
    static std::shared_ptr<IObject> createObject(const std::string &type, const libconfig::Setting &info);

    static std::shared_ptr<IObject> createSphere(const libconfig::Setting &info);

    static std::shared_ptr<IObject> createPlane(const libconfig::Setting &info);

    static std::shared_ptr<IObject> createCylinder(const libconfig::Setting &info);

    static std::shared_ptr<IObject> createCone(const libconfig::Setting &info);

    static std::shared_ptr<IObject> createCube(const libconfig::Setting &info);
};
    // std::shared_ptr<RayTracer::IObject> makeObject(const std::string &path, const RayTracer::HittableList & list);
    // ObjectFactory(/* args */);
    // ~ObjectFactory();
}
