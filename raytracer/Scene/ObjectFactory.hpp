#pragma once

#include "../Core/IObject.hpp"
#include <functional>
#include <string>
#include <unordered_map>

class ObjectFactory
{
private:
    using FactoryFunc = std::function<std::shared_ptr<RayTracer::IObject>(const std::string &)>;
    static std::unordered_map<std::string, FactoryFunc> _funcMap;
public:
    std::shared_ptr<RayTracer::IObject> makeObject(const std::string &shape);
    ObjectFactory(/* args */);
    ~ObjectFactory();
};
