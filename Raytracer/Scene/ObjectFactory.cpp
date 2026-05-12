#include "ObjectFactory.hpp"
#include "../Materials/FlatColor.hpp"
#include "../Materials/Reflection.hpp"

namespace {
    std::shared_ptr<RayTracer::IMaterial> createMaterial(const Color &color, const std::string &material)
    {
        if (material == "reflection")
            return std::make_shared<RayTracer::Reflection>(color);
        return std::make_shared<RayTracer::FlatColor>(color);
    }
}

namespace RayTracer {
    std::unique_ptr<IObject> ObjectFactory::createSphere(const libconfig::Setting &s)
    {
        return std::unique_ptr<IObject>(new Sphere(s));
    }

    std::unique_ptr<IObject> ObjectFactory::createPlane(
        const std::string &axisStr,
        int position,
        int cr, int cg, int cb,
        const std::string &material)
    {
        Axis axis = Axis::Y;
        if (axisStr == "X") axis = Axis::X;
        else if (axisStr == "Z") axis = Axis::Z;
        Color color(cr / 255.0, cg / 255.0, cb / 255.0);

        return std::unique_ptr<IObject>(
                new Plane(
                    axis,
                    position,
                    color,
                    createMaterial(color, material)
                )
            );
        }

    std::unique_ptr<IObject> ObjectFactory::createCylinder(
        int x, int y, int z,
        int r,
        int height,
        int cr, int cg, int cb,
        const std::string &material)
    {
        Color color(cr / 255.0, cg / 255.0, cb / 255.0);
        return std::unique_ptr<IObject>(
            new Cylinder(
                Math::Point3D(x, y, z),
                r,
                height,
                color,
                createMaterial(color, material)
            )
        );
    }

    std::unique_ptr<IObject> ObjectFactory::createCone(
        int x, int y, int z,
        int r,
        int height,
        int cr, int cg, int cb,
        const std::string &material)
    {
        Color color(cr / 255.0, cg / 255.0, cb / 255.0);
        return std::unique_ptr<IObject>(
            new Cone(
                Math::Point3D(x, y, z),
                r,
                height,
                color,
                createMaterial(color, material)
            )
        );
    }

    std::unique_ptr<IObject> ObjectFactory::createCube(
        int x, int y, int z,
        int width, int height, int depth,
        int cr, int cg, int cb,
        const std::string &material)
    {
        Color color(cr / 255.0, cg / 255.0, cb / 255.0);
        return std::unique_ptr<IObject>(
            new Cube(
                Math::Point3D(x, y, z),
                width,
                height,
                depth,
                createMaterial(color, material)
            )
        );
    }
}
