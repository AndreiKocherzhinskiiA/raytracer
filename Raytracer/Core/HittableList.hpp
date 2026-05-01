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
        size_t size() const { return objects.size(); }
        bool hit(const RayTracer::Ray& r, HitObject& rec, double tMin, double tMax) const override {
            HitObject tempRec;
            bool hitAnything = false;
            auto closest_so_far = tMax;

            for (const auto& obj : objects) {
                if (obj->hit(r, tempRec, tMin, closest_so_far)) {
                    hitAnything = true;
                    closest_so_far = tempRec.t;
                    rec = tempRec;
                }
            }
            return hitAnything;
        }
    };
}
