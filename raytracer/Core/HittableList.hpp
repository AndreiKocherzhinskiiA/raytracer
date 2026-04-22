#pragma once

#include "HitObject.hpp"
#include "IObject.hpp"
#include <vector>
#include <memory>

class HittableList : public RayTracer::IObject
{
private:
    std::vector<std::shared_ptr<RayTracer::IObject>> objects;

public:
    void add(std::shared_ptr<RayTracer::IObject> obj) {
        objects.push_back(obj);
    }

    bool hit(const RayTracer::Ray& r, double tMin, double tMax, HitObject& rec) const override {
        HitObject tempRec;
        bool hitAnything = false;

        for (const auto& obj : objects) {
            if (obj->hit(r, tMin, tMax, tempRec)) {
                hitAnything = true;
                tMax = tempRec.t;
                rec = tempRec;
            }
        }
        return hitAnything;
    }
};
