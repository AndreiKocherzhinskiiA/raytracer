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

    void Scene::parseSpheres(const libconfig::Setting &spheres)
    {
        for (int i = 0; i < spheres.getLength(); i++) {
            objects.push_back(
                ObjectFactory::createSphere(spheres[i])
                );
            }
        }

     void Scene::parsePlanes(const libconfig::Setting &planes)
    {
        for (int i = 0; i < planes.getLength(); i++) {
            const auto &p = planes[i];

            std::string axis = "Y";
            int position = 0;
            int cr = 255, cg = 255, cb = 255;
            std::string material = "flat";

            p.lookupValue("axis", axis);
            p.lookupValue("position", position);
            p.lookupValue("material", material);

            if (p.exists("color")) {
                const auto &color = p["color"];
                color.lookupValue("r", cr);
                color.lookupValue("g", cg);
                color.lookupValue("b", cb);
            }
            
            objects.push_back(
                ObjectFactory::createPlane(axis, position, cr, cg, cb, material)
                );
            }
        }    

    void Scene::parseCylinders(const libconfig::Setting &cylinders)
    {
        for (int i = 0; i < cylinders.getLength(); i++) {
            const auto &c = cylinders[i];

            int x = 0, y = 0, z = 0;
            int r = 0;
            int height = 100;
            int cr = 255, cg = 255, cb = 255;
            std::string material = "flat";

            c.lookupValue("x", x);
            c.lookupValue("y", y);
            c.lookupValue("z", z);
            c.lookupValue("r", r);
            c.lookupValue("height", height);
            c.lookupValue("material", material);

            if (c.exists("color")) {
                const auto &color = c["color"];
                color.lookupValue("r", cr);
                color.lookupValue("g", cg);
                color.lookupValue("b", cb);
            }

            objects.push_back(
                ObjectFactory::createCylinder(x, y, z, r, height, cr, cg, cb, material)
            );
        }
    }

    void Scene::parseCones(const libconfig::Setting &cones)
    {
        for (int i = 0; i < cones.getLength(); i++) {
            const auto &c = cones[i];

            int x = 0, y = 0, z = 0;
            int r = 0;
            int height = 100;
            int cr = 255, cg = 255, cb = 255;
            std::string material = "flat";

            c.lookupValue("x", x);
            c.lookupValue("y", y);
            c.lookupValue("z", z);
            c.lookupValue("r", r);
            c.lookupValue("height", height);
            c.lookupValue("material", material);

            if (c.exists("color")) {
                const auto &color = c["color"];
                color.lookupValue("r", cr);
                color.lookupValue("g", cg);
                color.lookupValue("b", cb);
            }

            objects.push_back(
                ObjectFactory::createCone(x, y, z, r, height, cr, cg, cb, material)
            );
        }
    }

    void Scene::parseCubes(const libconfig::Setting &cubes)
    {
        for (int i = 0; i < cubes.getLength(); i++) {
            const auto &c = cubes[i];

            int x = 0, y = 0, z = 0;
            int size = 50;
            int width = 50, height = 50, depth = 50;
            int cr = 255, cg = 255, cb = 255;
            std::string material = "flat";

            c.lookupValue("x", x);
            c.lookupValue("y", y);
            c.lookupValue("z", z);
            if (c.lookupValue("size", size)) {
                width = size;
                height = size;
                depth = size;
            }
            c.lookupValue("width", width);
            c.lookupValue("height", height);
            c.lookupValue("depth", depth);
            c.lookupValue("material", material);

            if (c.exists("color")) {
                const auto &color = c["color"];
                color.lookupValue("r", cr);
                color.lookupValue("g", cg);
                color.lookupValue("b", cb);
            }

            objects.push_back(
                ObjectFactory::createCube(x, y, z, width, height, depth, cr, cg, cb, material)
            );
        }
    }
    
    void Scene::loadObjects(const libconfig::Setting &primitives)
    {
        if (primitives.exists("spheres"))
            parseSpheres(primitives["spheres"]);

        if (primitives.exists("planes"))
            parsePlanes(primitives["planes"]);

        if (primitives.exists("cylinders"))
            parseCylinders(primitives["cylinders"]);

        if (primitives.exists("cones"))
            parseCones(primitives["cones"]);

        if (primitives.exists("cubes"))
            parseCubes(primitives["cubes"]);
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
                int x = 0;
                int y = 0;
                int z = 0;
                int cr = 255;
                int cg = 255;
                int cb = 255;

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
                int x = 0;
                int y = 0;
                int z = 0;
                int cr = 255;
                int cg = 255;
                int cb = 255;

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
