#pragma once
#include "Camera.hpp"
#include "../Core/HittableList.hpp"
#include "../Core/Lights.hpp"
#include "ObjectFactory.hpp"
#include <string>
#include <libconfig.h++>
#include "../Lights/Directional.hpp"
#include "../Lights/Point.hpp"


namespace RayTracer {
    class Scene
    {
    private:
        void loadCam(const libconfig::Setting &camera);
        void loadObjects(const libconfig::Setting &primitives);
        void loadLights(const libconfig::Setting &lights);

    public:
        Camera cam;
        HittableList hittable_list;
        Lights scene_lights;
        double ambient = 0;
        double diffuse = 1;
        Scene();
        bool init(const std::string &path);
        ~Scene() = default;
};

}

