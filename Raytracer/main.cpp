#include "./Core/HitObject.hpp"
#include "math/Ray.hpp"
#include "Scene/Rectangle3D.hpp"
#include "Scene/Camera.hpp"
#include "Primitives/Sphere.hpp"
#include <iostream>
#include <string>
#include "Core/Color.hpp"
#include "Core/HittableList.hpp"
#include "Core/Renderer.hpp"
#include "Core/Renderer.hpp"


int main(int argc, char **args)
{
    if (argc != 2) {
        std::cout <<  "./raytracer --help \n"
        << "USAGE: ./raytracer <SCENE_FILE> \n"
        << "SCENE_FILE: scene configuration" << std::endl;
        return 84;
    }
    RayTracer::Scene scene;
    scene.init(args[1]);
    RayTracer::Renderer renderer(scene);
    renderer.render();
    return 0;
}