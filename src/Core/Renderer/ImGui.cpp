
/*
 * There is no need to call an initializer as "initialization" is conducted inside the constructor.
 */

#include "ImGui.hpp"

#include <imgui_impl_opengl3.h>
#include <imgui_impl_win32.h>
#include <memory>
#include <ranges>
#include <Core/Graphics/OpenGL.hpp>
#include <UI/Element.hpp>

namespace akairo::Renderer
{
    ImGui::ImGui(BackendType backend, int width, int height): Interface(backend, width, height)
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
        switch (backendType)
        {
        case OpenGL:
            {
                ImGui_ImplOpenGL3_NewFrame();
                ImGui_ImplWin32_NewFrame();
                ::ImGui::NewFrame();

                extra();
                for (const auto& element : elements | std::views::values)
                {
                    if (element->Visible) element->Draw();
                }

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
