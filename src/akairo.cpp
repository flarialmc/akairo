#include "akairo.hpp"

#include "Core/Renderer/ImGui.hpp"

namespace akairo
{
  bool CreateRenderer(const std::string& name, Renderer::BackendType backend, Renderer::FrameworkType framework, int Width, int Height) {

    if (renderers.find(name) != renderers.end()) return false;

    switch (framework) {
    case Renderer::FrameworkType::ImGUI:
      {
        renderers[name] = std::make_shared<Renderer::ImGui>(Renderer::OpenGL, Width, Height);
        std::cout << "Created ImGui renderer with name: " << name << " " << renderers[name] << std::endl;
        break;
        /*
         * This is a test to see if the renderer is working.
         * It will create a rectangle and draw it.
         */


        /*
        auto rect = renderers[name]->CreateElement<Shapes::Rectangle>(
          "base rectangle", Components::Position(0.5f, {}));
        rect->Draw();
        */
      }
    case Renderer::FrameworkType::D2D: break;//renderers[name] = new OpenGL(backend);
    case Renderer::FrameworkType::UndefinedFramework: break;
    }
    return true;
  };

std::shared_ptr<Renderer::Interface> GetRenderer(const std::string& name)
  {
    if (renderers.contains(name)) return renderers[name];
    return nullptr;
  }
};
