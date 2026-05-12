#pragma once

#include "../Core/IObject.hpp"
#include <functional>
#include <string>
#include <unordered_map>
#include "../Primitives/Sphere.hpp"
#include "../Primitives/Plane.hpp"
#include "../Primitives/Cylinder.hpp"
#include "../Primitives/Cone.hpp"
#include "../Primitives/Cube.hpp"

// #include 

//NEED TO GET SHAPE FROM coning file.

namespace RayTracer {

class ObjectFactory {
// private:
//     using FactoryFunc = std::function<std::shared_ptr<RayTracer::IObject>(const std::string &)>;
//     static std::unordered_map<std::string, FactoryFunc> _funcMap;
public:
    static std::unique_ptr<IObject> createSphere(const libconfig::Setting &info);

    static std::unique_ptr<IObject> createPlane(const libconfig::Setting &info);

    static std::unique_ptr<IObject> createCylinder(
        int x, int y, int z,
        int r,
        int height,
        int cr, int cg, int cb,
        const std::string &material);

    static std::unique_ptr<IObject> createCone(
        int x, int y, int z,
        int r,
        int height,
        int cr, int cg, int cb,
        const std::string &material);

    static std::unique_ptr<IObject> createCube(
        int x, int y, int z,
        int width, int height, int depth,
        int cr, int cg, int cb,
        const std::string &material);
};
    // std::shared_ptr<RayTracer::IObject> makeObject(const std::string &path, const RayTracer::HittableList & list);
    // ObjectFactory(/* args */);
    // ~ObjectFactory();
}
