#pragma once
#include <iostream>
#include <unordered_map>
#include "Renderer/Renderer.hpp"


class akairo {

  static std::unordered_map<std::string, Renderer*> renderers;

  public:
    static bool CreateRenderer(const std::string& name, Renderer::Backends RendererBackend, Renderer::Frameworks RendererFramework);

    static Renderer* GetRenderer(const std::string& name);
};
