#pragma once
#include "Camera.hpp"
#include "../Core/Lights.hpp"
#include "ObjectFactory.hpp"
#include <string>
#include <libconfig.h++>
#include "../Lights/Directional.hpp"
#include "../Lights/Point.hpp"
#include "../Primitives/Plane.hpp"


namespace RayTracer {
    class Scene
    {
    private:
        void loadCam(const libconfig::Setting &camera);
        void loadLights(const libconfig::Setting &lights);
        void parseSpheres(const libconfig::Setting &spheres);
        void parsePlanes(const libconfig::Setting &planes);
        void parseCylinders(const libconfig::Setting &cylinders);
        void parseCones(const libconfig::Setting &cones);
        void parseCubes(const libconfig::Setting &cubes);
        void loadObjects(const libconfig::Setting &primitives);

    public:
        Camera cam;
        std::vector<std::shared_ptr<IObject>> objects;
        Lights scene_lights;
        double ambient = 0;
        double diffuse = 1;
        Scene();
        bool init(const std::string &path);
        ~Scene() = default;
};

}
