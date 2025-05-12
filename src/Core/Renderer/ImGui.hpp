#pragma once
#include "Interface.hpp"
#include <imgui.h>
#include <memory>
#include <Core/Graphics/IGraphicsHandler.hpp>
#include <Core/Graphics/OpenGL.hpp>
#include <backends/imgui_impl_opengl3.h>

namespace akairo::Renderer {
    class ImGui : public Interface {
        ImGuiContext* context;
        ImGuiIO* io;
        std::unique_ptr<Graphics::OpenGL> OpenGL;

        public:
         ImGui(BackendType backend, int Width, int Height);
    };

}
