#include "akairo.hpp"

#include <Core/Renderer/ImGui.hpp>

bool akairo::CreateRenderer(const std::string& name, Renderer::BackendType backend, Renderer::FrameworkType framework, int Width, int Height) {

  if (renderers.find(name) != renderers.end()) return false;

  switch (framework) {
    case Renderer::FrameworkType::ImGUI: renderers[name] = new Renderer::ImGui(Renderer::OpenGL, Width, Height); break;
    case Renderer::FrameworkType::D2D: break;//renderers[name] = new OpenGL(backend);
    case Renderer::FrameworkType::UndefinedFramework: ;
  }
  return true;
};

akairo::Renderer::Interface* akairo::GetRenderer(const std::string& name)
{
  if (renderers.find(name) != renderers.end()) return renderers[name];
  return nullptr;
}
