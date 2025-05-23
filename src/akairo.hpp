#pragma once
#include <iostream>
#include <unordered_map>
#include <Core/Renderer/Interface.hpp>



namespace akairo {

    static std::unordered_map<std::string, std::unique_ptr<Renderer::Interface>> renderers;
    static bool CreateRenderer(const std::string& name, Renderer::BackendType backend, Renderer::FrameworkType framework, int Width, int Height);

    static std::unique_ptr<Renderer::Interface> GetRenderer(const std::string& name);
};