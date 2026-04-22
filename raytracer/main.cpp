#include "math/Ray.hpp"
#include "Scene/Rectangle3D.hpp"
#include "Scene/Camera.hpp"
#include "Primitives/Sphere.hpp"
#include <iostream>
#include <string>
#include "Core/Color.hpp"
#include "Core/HittableList.hpp"
#include "Core/Render.hpp"


int main()
{
    RayTracer::Camera cam;
    RayTracer::HittableList hittableList;
    RayTracer::Render(hittableList, cam);
    return 0;
}