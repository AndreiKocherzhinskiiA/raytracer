#pragma once

#include "../Core/IObject.hpp"
#include "../Core/ILight.hpp"
#include "../Core/IMaterial.hpp"
#include "DLLoader.hpp"
#include <libconfig.h++>
#include <string>
#include <memory>
#include <unordered_map>

template <typename T>
class Factory {
    public:
        static std::shared_ptr<T> create(const std::string &type, const libconfig::Setting &s)
        {
            return DLLoader<T>::getInstance("./plugins/" + type + ".so", s);
        }
};
