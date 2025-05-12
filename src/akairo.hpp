#pragma once
#include <iostream>
#include <unordered_map>
#include "Renderer/Renderer.hpp"

#pragma comment(lib, "opengl32.lib")


class akairo {

  static std::unordered_map<std::string, IRenderer*> renderers;

  public:
    static bool CreateRenderer(const std::string& name, IRenderer::Backends RendererBackend, IRenderer::Frameworks RendererFramework);

    static IRenderer* GetRenderer(const std::string& name);
};
