#include "Scene.hpp"

namespace RayTracer {
    Scene::Scene() {};

    void Scene::loadCam(const libconfig::Setting &camera)
    {
        int width = 0;
        int height = 0;
        int x = 0;
        int y = 0;
        int z = 0;
        int rx = 0;
        int ry = 0;
        int rz = 0;
        double fov = 0;

        camera["resolution"].lookupValue("width", width);
        camera["resolution"].lookupValue("height", height);
        camera["position"].lookupValue("x", x);
        camera["position"].lookupValue("y", y);
        camera["position"].lookupValue("z", z);
        camera["rotation"].lookupValue("x", rx);
        camera["rotation"].lookupValue("y", ry);
        camera["rotation"].lookupValue("z", rz);
        camera.lookupValue("fieldOfView", fov);

        cam = Camera(width, height, Math::Point3D(x, y, z), fov);
        cam.rotation = Math::Vector3D(rx, ry, rz);
        cam.makeScreen();
    };

    void Scene::loadObjects(const libconfig::Setting &primitives) {
        // if (!primitives.exists("spheres"))
        //     return;
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
                    Color(cr / 255.0, cg / 255.0, cb / 255.0)
                )
            );
        }

        if (primitives.exists("planes")) {
            const auto &planes = primitives["planes"];
            for (int i = 0; i < planes.getLength(); i++) {
                const auto &p = planes[i];

                std::string axisStr = "Y";
                int position = 0;
                int cr = 255, cg = 255, cb = 255;

                p.lookupValue("axis", axisStr);
                p.lookupValue("position", position);

                const auto &color = p["color"];
                color.lookupValue("r", cr);
                color.lookupValue("g", cg);
                color.lookupValue("b", cb);

                Axis axis = Axis::Y;
                if (axisStr == "X") axis = Axis::X;
                else if (axisStr == "Z") axis = Axis::Z;

                hittable_list.add(
                    ObjectFactory::createPlane(
                        axis,
                        position,
                        Color(cr / 255.0, cg / 255.0, cb / 255.0)
                    )
                );
            }
        }
    };
    void Scene::loadLights(const libconfig::Setting &lights)
    {
        lights.lookupValue("ambient", ambient);
        lights.lookupValue("diffuse", diffuse);

        if (lights.exists("point")) {
            const auto &points = lights["point"];
            for (int i = 0; i < points.getLength(); i++) {
                const auto &p = points[i];
                int x = 0;
                int y = 0;
                int z = 0;

                p.lookupValue("x", x);
                p.lookupValue("y", y);
                p.lookupValue("z", z);

                scene_lights.add(
                    std::make_unique<PointLight>(
                        Math::Point3D(x, y, z),
                        Color(1, 1, 1)
                    )
                );
            }
        }

        if (lights.exists("directional")) {
            const auto &directionals = lights["directional"];
            for (int i = 0; i < directionals.getLength(); i++) {
                const auto &d = directionals[i];
                int x = 0;
                int y = 0;
                int z = 0;

                d.lookupValue("x", x);
                d.lookupValue("y", y);
                d.lookupValue("z", z);

                scene_lights.add(
                    std::make_unique<Directional>(
                        Math::Vector3D(x, y, z),
                        Color(1, 1, 1)
                    )
                );
            }
        }
    }

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
        if (root.exists("lights"))
            loadLights(root["lights"]);
        return true;
    };
}