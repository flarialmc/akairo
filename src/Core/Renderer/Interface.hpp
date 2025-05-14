#pragma once
#include <memory>
#include <Core/Graphics/OpenGL.hpp>

#include "Element.hpp"
#include "Position.hpp"

namespace akairo::Renderer {

    enum BackendType {

        UndefinedBackend,
        DirectX11,
        OpenGL

     };

    enum FrameworkType
    {
        UndefinedFramework,
        ImGUI,
        D2D
    };

    enum OSType
    {
        Android,
        Windows
    };

    class Interface {
    public:
        virtual ~Interface() = default;
        BackendType backendType = OpenGL;
        std::unique_ptr<Graphics::Interface> backend{};

        explicit Interface(BackendType backend) {
            this->backendType = backend;
          }

        [[nodiscard]] bool Initialize() const;

        virtual void DrawRectangle(Components::Position pos) const;
    };


}
