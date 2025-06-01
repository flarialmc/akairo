#pragma once
#include <iostream>
#include <Core/Renderer/Interface.hpp>
#include <Core/Renderer/ImGui.hpp>
namespace akairo::Graphics {

    enum BackendType {

        UndefinedBackend,
        oDirectX11,
        oOpenGL

     };
    /*
     * This is 赤色's "Graphics Interface". This is supposed to be a backend device that will store necessary objects.
     * For example, in OpenGL not much is needed due to how easy initialization and it's use is.
     * But for DirectX11, DirectX11on12, and etc.
     * You may need multiple D3D devices to support you.
     * This is merely a storage object.
     */

    class Interface {
    public:
        virtual ~Interface() = default;
        virtual bool Initialize(int Width, int Height) = 0;
        virtual void Shutdown() = 0;
        virtual void Resize(int Width, int Height) = 0;
        int Width{};
        int Height{};

        std::unordered_map<std::string, std::shared_ptr<Renderer::Interface>> renderers;
        bool CreateRenderer(const std::string& name, Renderer::BackendType backend, Renderer::FrameworkType framework) {

            if (renderers.find(name) != renderers.end()) return false;

            switch (framework) {
            case Renderer::FrameworkType::ImGUI:
                {
                    renderers[name] = std::make_shared<Renderer::ImGui>(backend, Width, Height);
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
        std::shared_ptr<Renderer::Interface> GetRenderer(const std::string& name)   {
            if (renderers.find(name) != renderers.end()) return renderers[name];
            return nullptr;
        }
    };

}
