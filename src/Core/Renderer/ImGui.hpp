#pragma once
#include <imgui.h>
#include <memory>
#include <Core/Graphics/OpenGL.hpp>
#include <backends/imgui_impl_opengl3.h>

#include "Interface.hpp"

namespace akairo::Renderer {

    class ImGui final : public Interface {
        ImGuiContext* context{};
        ImGuiIO& io;
        ImDrawList* list{};
        std::unique_ptr<Graphics::OpenGL> OpenGL;

    public:
        ImGui(BackendType backend, int Width, int Height);
        ~ImGui() override = default;
        void DrawRectangle(Components::Position pos) const override;
    };

}
