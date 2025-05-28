#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include "Core/Graphics/Interface.hpp"

namespace akairo {



    extern std::unordered_map<std::string, std::shared_ptr<Graphics::Interface>> graphics;
    bool CreateGraphics(const std::string& name, Graphics::BackendType backend, int Width, int Height);
    std::shared_ptr<Graphics::Interface> GetGraphics(const std::string& name);
};