#include "ObjectFactory.hpp"

namespace RayTracer {
    std::unique_ptr<IObject> ObjectFactory::createSphere(
        int x, int y, int z,
        int r,
        int cr, int cg, int cb)
        {
        return std::unique_ptr<IObject>(
            new Sphere(
                Math::Point3D(x, y, z),
                r,
                Color(cr / 255.0, cg / 255.0, cb / 255.0)
            )
        );
    }

    std::unique_ptr<IObject> ObjectFactory::createPlane(
        const std::string &axisStr,
        int position,
        int cr, int cg, int cb)
    {
        Axis axis = Axis::Y;
        if (axisStr == "X") axis = Axis::X;
        else if (axisStr == "Z") axis = Axis::Z;

        return std::unique_ptr<IObject>(
                new Plane(
                    axis,
                    position,
                    Color(cr / 255.0, cg / 255.0, cb / 255.0)
                )
            );
        }

    std::unique_ptr<IObject> ObjectFactory::createCylinder(
        int x, int y, int z,
        int r,
        int height,
        int cr, int cg, int cb)
    {
        return std::unique_ptr<IObject>(
            new Cylinder(
                Math::Point3D(x, y, z),
                r,
                height,
                Color(cr / 255.0, cg / 255.0, cb / 255.0)
            )
        );
    }
}