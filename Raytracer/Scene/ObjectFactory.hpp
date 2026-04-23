#pragma once

#include "../Core/IObject.hpp"
#include <functional>
#include <string>
#include <unordered_map>
#include "../Core/HittableList.hpp"
// #include 

//NEED TO GET SHAPE FROM coning file.
class ObjectFactory
{
private:
    using FactoryFunc = std::function<std::shared_ptr<RayTracer::IObject>(const std::string &)>;
    static std::unordered_map<std::string, FactoryFunc> _funcMap;
public:
    std::shared_ptr<RayTracer::IObject> makeObject(const std::string &path, const RayTracer::HittableList & list);
    ObjectFactory(/* args */);
    ~ObjectFactory();
};
