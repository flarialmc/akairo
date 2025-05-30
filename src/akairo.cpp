#include "akairo.hpp"

#include <Core/Graphics/OpenGL.hpp>

namespace akairo
{

    std::unordered_map<std::string, std::shared_ptr<Graphics::Interface>> graphics;
    bool CreateGraphics(const std::string& name, Graphics::BackendType backend, int Width, int Height) {
        if (graphics.find(name) != graphics.end()) return false;

        switch (backend) {
            case Graphics::BackendType::oOpenGL: {
                graphics[name] = std::make_shared<Graphics::OpenGL>(Width, Height);
                std::cout << "Created ImGui renderer with name: " << name << " " << graphics[name] << std::endl;
                break;
            }
            case Graphics::UndefinedBackend: break;
        default: ;
        }
        return true;
    };

    std::shared_ptr<Graphics::Interface> GetGraphics(const std::string& name)
    {
        if (graphics.contains(name)) return graphics[name];
        return nullptr;
    }
};
