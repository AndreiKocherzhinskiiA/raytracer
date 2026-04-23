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

    public:
        Scene();
        void loadCam();
        void loadObjects();
        void init(std::string path);
        ~Scene() = default;
};

}

