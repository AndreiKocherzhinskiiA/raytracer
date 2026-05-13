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
            Camera _cam;
            std::vector<std::shared_ptr<IObject>> _objects;
            Lights _lights;
            double _ambient = 0;
            double _diffuse = 1;

            void loadCam(const libconfig::Setting &camera);
            void loadLights(const libconfig::Setting &lights);
            void loadObjects(const libconfig::Setting &primitives);
        public:
            Scene();
            bool init(const std::string &path);
            ~Scene() = default;

            const Camera &cam() const { return _cam; }
            const std::vector<std::shared_ptr<IObject>> &objects() const { return _objects; }
            const Lights &lights() const { return _lights; }
            double ambient() const { return _ambient; }
            double diffuse() const { return _diffuse; }
        };
} // namespace RayTracer