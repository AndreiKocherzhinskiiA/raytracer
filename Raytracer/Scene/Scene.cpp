#include "Scene.hpp"
#include <iostream>

namespace RayTracer {
    Scene::Scene() {};

    void Scene::loadCam(const libconfig::Setting &camera)
    {
        int width, height, x, y, z, rx, ry, rz = 0;
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

    void Scene::loadObjects(const libconfig::Setting &primitives)
    {
        for (int i = 0; i < primitives.getLength(); i++) {
            const auto &primitiveGroup = primitives[i];
            const std::string type = primitiveGroup.getName();

            if (!ObjectFactory::hasType(type))
                continue;
            for (int j = 0; j < primitiveGroup.getLength(); j++)
                objects.push_back(ObjectFactory::createObject(type, primitiveGroup[j]));
        }
    }


    void Scene::loadLights(const libconfig::Setting &lights)
    {
        lights.lookupValue("ambient", ambient);
        lights.lookupValue("diffuse", diffuse);
        // std::cout << ambient << std::endl;
        // std::cout << diffuse << std::endl;
        if (lights.exists("point")) {
            const auto &points = lights["point"];
            for (int i = 0; i < points.getLength(); i++) {
                const auto &p = points[i];
                int x, y, z = 0;
                int cr, cg, cb = 255;

                p.lookupValue("x", x);
                p.lookupValue("y", y);
                p.lookupValue("z", z);
                if (p.exists("color")) {
                    const auto &color = p["color"];
                    color.lookupValue("r", cr);
                    color.lookupValue("g", cg);
                    color.lookupValue("b", cb);
                }

                scene_lights.add(
                    std::make_unique<PointLight>(
                        Math::Point3D(x, y, z),
                        Color(cr / 255.0, cg / 255.0, cb / 255.0)
                    )
                );
            }
        }

        if (lights.exists("directional")) {
            const auto &directionals = lights["directional"];
            for (int i = 0; i < directionals.getLength(); i++) {
                const auto &d = directionals[i];
                int x, y, z = 0;
                int cr, cg, cb = 255;

                d.lookupValue("x", x);
                d.lookupValue("y", y);
                d.lookupValue("z", z);
                if (d.exists("color")) {
                    const auto &color = d["color"];
                    color.lookupValue("r", cr);
                    color.lookupValue("g", cg);
                    color.lookupValue("b", cb);
                }

                scene_lights.add(
                    std::make_unique<Directional>(
                        Math::Vector3D(x, y, z),
                        Color(cr / 255.0, cg / 255.0, cb / 255.0)
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
