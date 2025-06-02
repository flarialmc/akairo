
/*
 * There is no need to call an initializer as "initialization" is conducted inside the constructor.
 */

#include "ImGui.hpp"

#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_internal.h>
#include <ranges>
#include <imgui_impl_win32.h>
#include <memory>
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
    void ImGui::DrawRectangle(Components::Position pos, Components::Size size, Components::Color color, Components::Rounding rounding) const
    {
        ImVec2<float> p_min = pos.ProperPosition.getImVec2();
        ImVec2<float> p_max = size.ProperSize.getImVec2();

        float tl_rounding = ImMin(rounding.TopLeft, ImMin((p_max.x - p_min.x) * 0.5f, (p_max.y - p_min.y) * 0.5f));
        float tr_rounding = ImMin(rounding.TopRight, ImMin((p_max.x - p_min.x) * 0.5f, (p_max.y - p_min.y) * 0.5f));
        float bl_rounding = ImMin(rounding.BottomLeft, ImMin((p_max.x - p_min.x) * 0.5f, (p_max.y - p_min.y) * 0.5f));
        float br_rounding = ImMin(rounding.BottomRight, ImMin((p_max.x - p_min.x) * 0.5f, (p_max.y - p_min.y) * 0.5f));

        ImVec2 c_tl = ImVec2(p_min.x + tl_rounding, p_min.y + tl_rounding);
        ImVec2 c_tr = ImVec2(p_max.x - tr_rounding, p_min.y + tr_rounding);
        ImVec2 c_bl = ImVec2(p_min.x + bl_rounding, p_max.y - bl_rounding);
        ImVec2 c_br = ImVec2(p_max.x - br_rounding, p_max.y - br_rounding);

        ImDrawList *draw_list = ::ImGui::GetBackgroundDrawList();

        draw_list->PathClear();

        // Top-left corner
        if (tl_rounding > 0.0f) draw_list->PathArcTo(c_tl, tl_rounding, IM_PI * 1.0f, IM_PI * 1.5f, 10);
            // 180 to 270 degrees
        else draw_list->PathLineTo(p_min); // If no rounding, draw straight corner
        draw_list->PathLineTo(ImVec2(c_tr.x, p_min.y));

        // Top-right corner
        if (tr_rounding > 0.0f) draw_list->PathArcTo(c_tr, tr_rounding, IM_PI * 1.5f, IM_PI * 2.0f, 10);
            // 270 to 360 degrees
        else draw_list->PathLineTo(ImVec2(p_max.x, p_min.y));
        draw_list->PathLineTo(ImVec2(p_max.x, c_br.y));

        // Bottom-right corner
        if (br_rounding > 0.0f) draw_list->PathArcTo(c_br, br_rounding, IM_PI * 0.0f, IM_PI * 0.5f, 10);
            // 0 to 90 degrees
        else draw_list->PathLineTo(p_max);
        draw_list->PathLineTo(ImVec2(c_bl.x, p_max.y));

        // Bottom-left corner
        if (bl_rounding > 0.0f) draw_list->PathArcTo(c_bl, bl_rounding, IM_PI * 0.5f, IM_PI * 1.0f, 10);
            // 90 to 180 degrees
        else draw_list->PathLineTo(ImVec2(p_min.x, p_max.y));
        draw_list->PathLineTo(ImVec2(p_min.x, c_tl.y));

        draw_list->PathFillConvex(color.toImColor()); // Fill the created path
        // ::ImGui::GetBackgroundDrawList()->AddRectFilled(
        // pos.ProperPosition.getImVec2(),
        // size.ProperSize.getImVec2(),
        // color.toImColor(),
        // 0,
        // 240
        // );
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
