#pragma once

#include "HitObject.hpp"
#include "IObject.hpp"
#include <vector>
#include <memory>


namespace RayTracer {
    class HittableList : public RayTracer::IObject
    {
    private:
        std::vector<std::shared_ptr<RayTracer::IObject>> objects;

    public:
        void add(std::shared_ptr<RayTracer::IObject> obj) {
            objects.push_back(obj);
        }

        bool hit(const RayTracer::Ray& r, HitObject& rec, double tMin, double tMax) const override {
            HitObject tempRec;
            bool hitAnything = false;

            for (const auto& obj : objects) {
                if (obj->hit(r, tempRec, tMin, tMax)) {
                    hitAnything = true;
                    tMax = tempRec.t;
                    rec = tempRec;
                }
            }
            return hitAnything;
        }
    };
}
