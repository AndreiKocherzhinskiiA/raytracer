#include "Scene.hpp"

namespace RayTracer {
        Scene::Scene() {

        };
        void Scene::loadCam(const libconfig::Setting &camera) 
        {
            int width = 0;
            int height = 0;
            int x = 0;
            int y = 0;
            int z = 0;
            double fov = 0;

            camera["resolution"].lookupValue("width", width);
            camera["resolution"].lookupValue("height", height);
            camera["position"].lookupValue("x", x);
            camera["position"].lookupValue("y", y);
            camera["position"].lookupValue("z", z);
            camera.lookupValue("fieldOfView", fov);
            Math::Point3D origin(x, y, z);
            cam = Camera(width, height, origin, fov);
            //cam = Camera(width, height, Point3D(x, y, z), fov);
        };

        
        void Scene::loadObjects(const libconfig::Setting &primitives) {
            if (!primitives.exists("spheres")) {
                return;
            }
            const auto &spheres = primitives["spheres"];
            for (int i = 0; i < spheres.getLength(); i++) {
                const auto &s = spheres[i];
                int x = 0;
                int y = 0;
                int z = 0;
                int r = 0;
                s.lookupValue("x", x);
                s.lookupValue("y", y);
                s.lookupValue("z", z);
                s.lookupValue("r", r);
                const auto &color = s["color"];
                int cr = 0;
                int cg = 0;
                int cb = 0;
                color.lookupValue("r", cr);
                color.lookupValue("g", cg);
                color.lookupValue("b", cb);
                hittable_list.add(
                    ObjectFactory::createSphere(
                        Math::Point3D(x, y, z),
                        r,
                        Color(cr, cg, cb)
                    )
                );
            }
        };
        bool Scene::init(const std::string &path) {
            libconfig::Config cfg;

            try {
                cfg.readFile(path.c_str());
            } catch (const libconfig::FileIOException &e) {
                std::cerr << "File IO error\n";
                return false;
            } catch (const libconfig::ParseException &e) {
                std::cerr << "Parse error at " << e.getFile()
                          << " ; " << e.getLine()
                          << " - " << e.getError() << "\n";
                return false;
            }

            const libconfig::Setting &root = cfg.getRoot();

            loadCam(root["camera"]);
            loadObjects(root["primitives"]);
            // loadLights(root["lights"]);
            return true;
        };
}

