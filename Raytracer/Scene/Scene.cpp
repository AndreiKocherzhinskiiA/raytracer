#include "Scene.hpp"

namespace RayTracer {
        Scene::Scene() {

        };
        void Scene::loadCam(const libconfig::Setting &camera) 
        {
            const auto &res = camera["resolution"];
            int width = res["width"];
            int height = res["height"];

            const auto &pos = camera["position"];
            double x = pos["x"];
            double y = pos["y"];
            double z = pos["z"];

            double fov = camera["fieldofView"];

            Math::Point3D origin(x, y, z);
            cam = Camera(width, height, origin, fov);
            //cam = Camera(width, height, Point3D(x, y, z), fov);
        };
        void Scene::loadObjects(const libconfig::Setting &primitives) {
            if (primitives.exists("spheres")) {
                const auto &spheres = primitives["spheres"];

                for (int i = 0; i < spheres.getLength(); i++) {
                    const auto &s = spheres[i];

                    double x = s["x"];
                    double y = s["y"];
                    double z = s["z"];
                    double r = s["r"];

                    const auto &color = s["color"];
                    int cr = color["r"];
                    int cg = color["g"];
                    int cb = color["b"];

                    hittable_list.add(
                        ObjectFactory::createSphere(
                            Point3D(x, y, z),
                            r,
                            Color(cr, cg, cb)
                        )
                    );
                }
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
            loadLights(root["lights"]);
            return true;
        };
}

