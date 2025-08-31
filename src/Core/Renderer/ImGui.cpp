
/*
 * There is no need to call an initializer as "initialization" is conducted inside the constructor.
 */

#include "ImGui.hpp"


#include <imgui_impl_opengl3.h>
#include <ranges>
#include <imgui_impl_win32.h>
#include <imgui_internal.h>
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

    void ImGui::PushClipRect(const Components::Position& pos,
                             const Components::Size& size,
                             bool intersect_with_current = true)
    {
        ImVec2 min = pos.ProperPosition.getImVec2();
        ImVec2 max = (pos.ProperPosition + size.ProperSize).getImVec2();

        ::ImGui::GetBackgroundDrawList()->PushClipRect(min, max);
    }

    void ImGui::PopClipRect()
    {
        ::ImGui::GetBackgroundDrawList()->PopClipRect();
    }
 void ImGui::DrawRectangle(const Components::Position pos,
                          const Components::Size size,
                          const Components::Color color,
                          Components::Rounding rounding) const
{
    const ::ImVec2 p0 = pos.ProperPosition.getImVec2();
    const ::ImVec2 sz = size.ProperSize.getImVec2();

    if (sz.x <= 0.0f || sz.y <= 0.0f)
        return;

    const ::ImVec2 p1(p0.x + sz.x, p0.y + sz.y);

    const float w = sz.x;
    const float h = sz.y;
    const float rmax = ::ImMin(w, h) * 0.5f;

    const float tl = ::ImMin(rounding.properRounding.x, rmax);
    const float tr = ::ImMin(rounding.properRounding.y, rmax);
    const float br = ::ImMin(rounding.properRounding.w, rmax);
    const float bl = ::ImMin(rounding.properRounding.z, rmax);

    ::ImDrawList* draw_list = ::ImGui::GetBackgroundDrawList();
    draw_list->PathClear();

    const int num_segments = 16; // More segments = smoother arcs

    // Helper to generate a corner arc
    auto add_arc = [&](const ImVec2& center, float radius, float a_min, float a_max) {
        const float step = (a_max - a_min) / (float)num_segments;
        for (int i = 0; i <= num_segments; ++i) {
            float a = a_min + i * step;
            draw_list->PathLineTo(ImVec2(center.x + cosf(a) * radius, center.y + sinf(a) * radius));
        }
    };

    // Top-left corner
    if (tl > 0.0f)
        add_arc(ImVec2(p0.x + tl, p0.y + tl), tl, IM_PI, IM_PI * 1.5f);
    else
        draw_list->PathLineTo(p0);

    // Top-right corner
    if (tr > 0.0f)
        add_arc(ImVec2(p1.x - tr, p0.y + tr), tr, IM_PI * 1.5f, IM_PI * 2.0f);
    else
        draw_list->PathLineTo(ImVec2(p1.x, p0.y));

    // Bottom-right corner
    if (br > 0.0f)
        add_arc(ImVec2(p1.x - br, p1.y - br), br, 0.0f, IM_PI * 0.5f);
    else
        draw_list->PathLineTo(ImVec2(p1.x, p1.y));

    // Bottom-left corner
    if (bl > 0.0f)
        add_arc(ImVec2(p0.x + bl, p1.y - bl), bl, IM_PI * 0.5f, IM_PI);
    else
        draw_list->PathLineTo(ImVec2(p0.x, p1.y));

    // Fill the polygon (works for non-convex shapes too)
    draw_list->PathFillConvex(color.toImColor());
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
