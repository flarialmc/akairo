#pragma once
#include <imgui_internal.h>
#include <UI/Components/Color/Color.hpp>
#include <UI/Components/Position/Position.hpp>
#include <UI/Components/Size/Size.hpp>

#include "Interface.hpp"

namespace akairo::Renderer {

    class ImGui final : public Interface {
        ImGuiContext* context{};

    public:
        ImGui(BackendType backend);
        ~ImGui() override = default;
        void DrawRectangle(Components::Position pos, Components::Size size, Components::Color color) const override;
        void DrawHollowRectangle(Components::Position pos, Components::Size size, Components::Color color, float Width) const override;
        void DrawCircle(Components::Position pos, float radius, Components::Color color) const override;
        void Render(const std::function<void()>& extra) override;
    };

}
