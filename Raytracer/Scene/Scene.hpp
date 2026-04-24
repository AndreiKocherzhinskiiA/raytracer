#pragma once
#include "Camera.hpp"
#include "../Core/HittableList.hpp"
#include "../Core/IMaterial.hpp"
#include "../Core/Lights.hpp"
#include "ObjectFactory.hpp"
#include <string>
#include <libconfig.h++>


namespace RayTracer {
    class Scene
    {
    private:

    public:
        Camera cam;
        HittableList hittable_list;
        Lights lights;
        Scene();
        void loadCam();
        void loadObjects();
        void loadLights();
        void init(std::string path);
        ~Scene() = default;
};

}

