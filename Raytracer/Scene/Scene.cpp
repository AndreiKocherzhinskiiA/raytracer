#include "Scene.hpp"

namespace RayTracer {

        Scene::Scene() {

        };
        void Scene::loadCam() {

        };
        void Scene::loadObjects() {

        };

        void Scene::loadLights() {

        };
        void Scene::init(std::string path) {
                loadCam();
                loadObjects();
                loadLights();
        };
}

