#pragma once
#include <iostream>
#include <unordered_map>
#include <Core/Renderer/Interface.hpp>



#pragma comment(lib, "opengl32.lib")


namespace akairo {

    static std::unordered_map<std::string, Renderer::Interface*> renderers;
    static bool CreateRenderer(const std::string& name, Renderer::BackendType backend, Renderer::FrameworkType framework, int Width, int Height);

    static Renderer::Interface* GetRenderer(const std::string& name);
};