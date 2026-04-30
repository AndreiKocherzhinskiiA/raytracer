#include "ObjectFactory.hpp"

namespace RayTracer {
    std::shared_ptr<IObject> ObjectFactory::createSphere(
        const Math::Point3D &center,
        double radius,
        const Color &color
    ) {
        return std::make_shared<RayTracer::Sphere>(center, radius, color);
    }
}