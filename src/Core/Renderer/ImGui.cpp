#include "ImGui.hpp"

/*
 * There is no need to call an initializer as "initialization" is conducted inside the constructor.
 */

namespace akairo::Renderer
{
    ImGui::ImGui(BackendType backend, int Width, int Height): Interface(backend)
    {
        this->backend = std::make_unique<Graphics::OpenGL>(Width, Height);
        this->backendType = backend;

        switch (backend)
        {
        case BackendType::OpenGL: { ImGui_ImplOpenGL3_Init("#version 300 es"); }
        default:
            {
            }
        }

        this->context = ::ImGui::CreateContext();
        this->list = ::ImGui::GetBackgroundDrawList();
    }

    void ImGui::DrawRectangle(Components::Position pos, Components::Size size, Components::Color color) const
    {

        this->list->AddRectFilled(
            pos.ProperPosition.getImVec2(),
            (pos.ProperPosition + size.ProperSize).getImVec2(),
            color.toImColor(),
            0,
            240
        );
    }

    void ImGui::DrawHollowRectangle(Components::Position pos, Components::Size size, Components::Color color, float Width) const
    {
        this->list->AddRect(
            pos.ProperPosition.getImVec2(),
            (pos.ProperPosition + size.ProperSize).getImVec2(),
            color.toImColor(),
            0,
            240,
            Width);
    }

    void ImGui::DrawCircle(Components::Position pos, float radius, Components::Color color) const
    {
        this->list->AddCircleFilled(pos.ProperPosition.getImVec2(), radius, color.toImColor());
    }

}
