#pragma once

#include "Camera.hpp"
#include "../Core/IObject.hpp"
#include "../Core/ILight.hpp"
#include "../Core/Lights.hpp"
#include "Factory.hpp"
#include <string>
#include <vector>
#include <memory>
#include <libconfig.h++>

namespace RayTracer {

class Scene {
    private:
        void loadCam(const libconfig::Setting &camera);
        void loadLights(const libconfig::Setting &lights);
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

} // namespace RayTracer