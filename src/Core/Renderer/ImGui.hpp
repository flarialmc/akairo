#pragma once
#include <imgui.h>
#include <memory>
#include "Core/Graphics/OpenGL.hpp"
#include "Interface.hpp"
#include <backends/imgui_impl_opengl3.h>
namespace akairo::Renderer {

    class ImGui final : public Interface {
        ImGuiContext* context{};
        ImDrawList* list{};
        std::unique_ptr<Graphics::OpenGL> OpenGL;

    public:
        ImGui(BackendType backend, int Width, int Height);
        ~ImGui() override = default;
        void DrawRectangle(Components::Position pos, Components::Size size, Components::Color color) const override;
        void DrawHollowRectangle(Components::Position pos, Components::Size size, Components::Color color, float Width) const override;
        void DrawCircle(Components::Position pos, float radius, Components::Color color) const override;
    };

}
