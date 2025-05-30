
/*
 * There is no need to call an initializer as "initialization" is conducted inside the constructor.
 */

#include "ImGui.hpp"

#include <imgui_impl_opengl3.h>
#include <memory>
#include <Core/Graphics/OpenGL.hpp>

namespace akairo::Renderer
{
    ImGui::ImGui(BackendType backend): Interface(backend)
    {
        this->backendType = backend;

        this->context = ::ImGui::CreateContext();
        ::ImGui::SetCurrentContext(context);

        switch (backend)
        {
        case BackendType::OpenGL: { ImGui_ImplOpenGL3_Init("#version 130"); break; }
        default:
            {
                break;
            }
        }

    }

    void ImGui::Render(const std::function<void()>& extra)
    {
        ::ImGui::Render();
        switch (backendType)
        {
        case BackendType::OpenGL:
            {
                ImGui_ImplOpenGL3_NewFrame();
                ::ImGui::NewFrame();

                extra();

                ::ImGui::EndFrame();
                ::ImGui::Render();
                ImGui_ImplOpenGL3_RenderDrawData(::ImGui::GetDrawData());
                break;
            }
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
        size.ProperSize.getImVec2(),
        color.toImColor(),
        0,
        240
    );
    }

    void ImGui::DrawHollowRectangle(Components::Position pos, Components::Size size, Components::Color color, float Width) const
    {
        ::ImGui::GetBackgroundDrawList()->AddRect(
            pos.ProperPosition.getImVec2(),
            size.ProperSize.getImVec2(),
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
