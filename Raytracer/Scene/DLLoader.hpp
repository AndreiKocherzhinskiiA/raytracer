#pragma once

#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <dlfcn.h>
#include <libconfig.h++>

template <typename T>
class DLLoader {
    private:
        inline static std::unordered_map<std::string, void *> _cache;

        static void *getHandle(const std::string &lib)
        {
            auto it = _cache.find(lib);
            if (it != _cache.end())
                return it->second;
            void *handle = dlopen(lib.c_str(), RTLD_LAZY);
            if (!handle)
                throw std::runtime_error(dlerror());
            _cache[lib] = handle;
            return handle;
        }

    public:
        static std::shared_ptr<T> getInstance(const std::string &lib, const libconfig::Setting &s, const std::string &sym = "Create")
        {
            void *handle = getHandle(lib);
            void *raw = dlsym(handle, sym.c_str());
            if (!raw)
                throw std::runtime_error("Symbol not found in: " + lib);
            auto factory = reinterpret_cast<T *(*)(const libconfig::Setting &)>(raw);
            return std::shared_ptr<T>(factory(s));
        }

        static void unload(const std::string &lib)
        {
            auto it = _cache.find(lib);
            if (it != _cache.end()) {
                dlclose(it->second);
                _cache.erase(it);
            }
        }

        static void unloadAll()
        {
            for (auto &[path, handle] : _cache)
                dlclose(handle);
            _cache.clear();
        }
};