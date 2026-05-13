#include "Scene.hpp"
#include "Factory.hpp"
#include <iostream>

namespace RayTracer {

Scene::Scene() {}

void Scene::loadCam(const libconfig::Setting &camera)
{
    int width = 0, height = 0;
    int x = 0, y = 0, z = 0;
    int rx = 0, ry = 0, rz = 0;
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

    _cam = Camera(width, height, Math::Point3D(x, y, z), fov);
    _cam.rotation = Math::Vector3D(rx, ry, rz);
    _cam.makeScreen();
}

void Scene::loadObjects(const libconfig::Setting &primitives)
{
    for (int i = 0; i < primitives.getLength(); i++) {
        const auto &group = primitives[i];
        const std::string type = group.getName();

        for (int j = 0; j < group.getLength(); j++)
            _objects.push_back(Factory<IObject>::create(type, group[j]));
    }
}

void Scene::loadLights(const libconfig::Setting &lights)
{
    lights.lookupValue("ambient", _ambient);
    lights.lookupValue("diffuse", _diffuse);

    for (int i = 0; i < lights.getLength(); i++) {
        const auto &group = lights[i];
        const std::string type = group.getName();

        if (type == "ambient" || type == "diffuse")
            continue;
        for (int j = 0; j < group.getLength(); j++)
            _lights.add(Factory<ILight>::create(type, group[j]));
    }
}

bool Scene::init(const std::string &path)
{
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
}

} // namespace RayTracer