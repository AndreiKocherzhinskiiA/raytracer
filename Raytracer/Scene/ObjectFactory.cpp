#include "ObjectFactory.hpp"
#include "../Materials/FlatColor.hpp"
#include "../Materials/Reflection.hpp"
#include <stdexcept>

namespace {
    std::shared_ptr<RayTracer::IMaterial> createMaterial(const Color &color, const std::string &material)
    {
        if (material == "reflection")
            return std::make_shared<RayTracer::Reflection>(color);
        return std::make_shared<RayTracer::FlatColor>(color);
    }

    Color readColor(const libconfig::Setting &setting)
    {
        int r, g, b = 255;

        if (setting.exists("color")) {
            const auto &color = setting["color"];
            color.lookupValue("r", r);
            color.lookupValue("g", g);
            color.lookupValue("b", b);
        }
        return Color(r / 255.0, g / 255.0, b / 255.0);
    }

    std::string readMaterial(const libconfig::Setting &setting)
    {
        std::string material = "flat";

        setting.lookupValue("material", material);
        return material;
    }
}

namespace RayTracer {
    const std::unordered_map<std::string, ObjectFactory::FactoryFunc> &ObjectFactory::funcMap()
    {
        static const std::unordered_map<std::string, FactoryFunc> map = {
            {"spheres", &ObjectFactory::createSphere},
            {"planes", &ObjectFactory::createPlane},
            {"cylinders", &ObjectFactory::createCylinder},
            {"cones", &ObjectFactory::createCone},
            {"cubes", &ObjectFactory::createCube}
        };

        return map;
    }

    bool ObjectFactory::hasType(const std::string &type)
    {
        const auto &factories = funcMap();
        const auto factory = factories.find(type);

        return factory != factories.end();
    }

    std::shared_ptr<IObject> ObjectFactory::createObject(const std::string &type, const libconfig::Setting &info)
    {
        const auto it = funcMap().find(type);

        if (it == funcMap().end())
            throw std::runtime_error("Unsupported primitive type: " + type);
        return it->second(info);
    }

    std::shared_ptr<IObject> ObjectFactory::createSphere(const libconfig::Setting &s)
    {
        return std::make_shared<Sphere>(s);
    }

    std::shared_ptr<IObject> ObjectFactory::createPlane(const libconfig::Setting &s)
    {
        return std::make_shared<Plane>(s);
    }

    std::shared_ptr<IObject> ObjectFactory::createCylinder(const libconfig::Setting &c)
    {
        int x, y, z, r = 0;
        int height = 100;
        Color color = readColor(c);
        std::string material = readMaterial(c);

        c.lookupValue("x", x);
        c.lookupValue("y", y);
        c.lookupValue("z", z);
        c.lookupValue("r", r);
        c.lookupValue("height", height);
        return std::make_shared<Cylinder>(
            Math::Point3D(x, y, z),
            r,
            height,
            color,
            createMaterial(color, material)
        );
    }

    std::shared_ptr<IObject> ObjectFactory::createCone(const libconfig::Setting &c)
    {
        int x, y, z, r = 0;
        int height = 100;
        Color color = readColor(c);
        std::string material = readMaterial(c);

        c.lookupValue("x", x);
        c.lookupValue("y", y);
        c.lookupValue("z", z);
        c.lookupValue("r", r);
        c.lookupValue("height", height);
        return std::make_shared<Cone>(
            Math::Point3D(x, y, z),
            r,
            height,
            color,
            createMaterial(color, material)
        );
    }

    std::shared_ptr<IObject> ObjectFactory::createCube(const libconfig::Setting &c)
    {
        int x, y, z, r = 0;
        int size, width, height, depth = 50;
        Color color = readColor(c);
        std::string material = readMaterial(c);

        c.lookupValue("x", x);
        c.lookupValue("y", y);
        c.lookupValue("z", z);
        if (c.lookupValue("size", size)) {
            width = size;
            height = size;
            depth = size;
        }
        c.lookupValue("width", width);
        c.lookupValue("height", height);
        c.lookupValue("depth", depth);
        return std::make_shared<Cube>(
            Math::Point3D(x, y, z),
            width,
            height,
            depth,
            createMaterial(color, material)
        );
    }
}
