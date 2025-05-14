#include "akairo.hpp"
#include "Core/Renderer/ImGui.hpp"

bool akairo::CreateRenderer(const std::string& name, Renderer::BackendType backend, Renderer::FrameworkType framework, int Width, int Height) {

  if (renderers.find(name) != renderers.end()) return false;

  switch (framework) {
  case Renderer::FrameworkType::ImGUI:
    {
      renderers[name] = std::make_unique<Renderer::ImGui>(Renderer::OpenGL, Width, Height);
    }
    case Renderer::FrameworkType::D2D: break;//renderers[name] = new OpenGL(backend);
    case Renderer::FrameworkType::UndefinedFramework: ;
  }
  return true;
};

std::unique_ptr<akairo::Renderer::Interface> akairo::GetRenderer(const std::string& name)
{
  if (renderers.contains(name)) return std::move(renderers[name]);
  return nullptr;
}
