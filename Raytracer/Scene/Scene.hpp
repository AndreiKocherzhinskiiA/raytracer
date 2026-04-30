#pragma once
#include "Camera.hpp"
#include "../Core/HittableList.hpp"
#include "ObjectFactory.hpp"
#include <string>
#include <libconfig.h++>


namespace RayTracer {
    class Scene
    {
    private:
        Camera cam;
        HittableList hittable_list;

        void loadCam(const libconfig::Setting &camera);
        void loadObjects(const libconfig::Setting &primitives);
        void loadLights(const libconfig::Setting &lights);

    public:
        Scene();
        bool init(const std::string path);
        ~Scene() = default;
};

}

