#include "ImGui.hpp"

#include <iostream>
#include <ostream>

/*
 * There is no need to call an initializer as "initialization" is conducted inside the constructor.
 */

namespace akairo::Renderer
{
    ImGui::ImGui(BackendType backend, int Width, int Height): Interface(backend)
    {
        this->backend = std::make_unique<Graphics::OpenGL>(Width, Height);
        this->backendType = backend;

        std::cout << "Creating ImGui Context" << std::endl;


        this->context = ::ImGui::CreateContext();
        ::ImGui::SetCurrentContext(context);
        std::cout << "ImGui Context Created" << std::endl;

        switch (backend)
        {
        case BackendType::OpenGL: { ImGui_ImplOpenGL3_Init("#version 130"); break; }
        default:
            {
                break;
            }
        }

    }

    void ImGui::DrawRectangle(Components::Position pos, Components::Size size, Components::Color color) const
    {

        ::ImGui::GetBackgroundDrawList()->AddRectFilled(
            pos.ProperPosition.getImVec2(),
            (pos.ProperPosition + size.ProperSize).getImVec2(),
            color.toImColor(),
            0,
            240
        );
    }

    void ImGui::DrawHollowRectangle(Components::Position pos, Components::Size size, Components::Color color, float Width) const
    {
        ::ImGui::GetBackgroundDrawList()->AddRect(
            pos.ProperPosition.getImVec2(),
            (pos.ProperPosition + size.ProperSize).getImVec2(),
            color.toImColor(),
            0,
            240,
            Width);
    }

    void ImGui::DrawCircle(Components::Position pos, float radius, Components::Color color) const
    {
        ::ImGui::GetBackgroundDrawList()->AddCircleFilled(pos.ProperPosition.getImVec2(), radius, color.toImColor());
    }

}
