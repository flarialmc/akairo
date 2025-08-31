#pragma once


#include <UI/Components/Color/Color.hpp>
#include <UI/Components/Position/Position.hpp>
#include <UI/Components/Size/Size.hpp>
#include "Interface.hpp"

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#include <iostream>
#include <Windows.h>
#include <GL/gl.h>

#include "imgui_internal.h"

inline int g_StencilRef = 0;


inline void StencilClipSetup(const ImDrawList* parent_list, const ImDrawCmd* cmd) {
    (void)parent_list; // Unused
    g_StencilRef++;
    if (g_StencilRef == 1) {
        glClearStencil(0);
        glClear(GL_STENCIL_BUFFER_BIT);
    }
    glEnable(GL_STENCIL_TEST);
    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
    glDepthMask(GL_FALSE);
    glStencilFunc(GL_GEQUAL, g_StencilRef - 1, 0xFF);
    glStencilOp(GL_KEEP, GL_KEEP, GL_INCR);
    glStencilMask(0xFF);
}

inline void StencilClipStartDraw(const ImDrawList* parent_list, const ImDrawCmd* cmd) {
    (void)parent_list; // Unused
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    glDepthMask(GL_TRUE);
    glStencilFunc(GL_GEQUAL, g_StencilRef, 0xFF);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
    glStencilMask(0x00);
}

inline void StencilClipEnd(const ImDrawList* parent_list, const ImDrawCmd* cmd) {
    (void)parent_list; // Unused
    g_StencilRef--;
    if (g_StencilRef == 0) {
        glDisable(GL_STENCIL_TEST);
    } else {
        glStencilFunc(GL_GEQUAL, g_StencilRef, 0xFF);
    }
}


namespace akairo::Renderer {

    class ImGui final : public Interface {
        ImGuiContext* context{};

    public:
        explicit ImGui(BackendType backend, int width, int height);
        ~ImGui() override = default;
        static void PopClipRect();
        void DrawRectangle(Components::Position pos, Components::Size size, Components::Color color, Components::Rounding rounding) const override;
        void DrawHollowRectangle(Components::Position pos, Components::Size size, Components::Color color, float Width) const override;
        void DrawCircle(Components::Position pos, float radius, Components::Color color) const override;
        void Render(const std::function<void()>& extra) override;
        static void PushClipRect(const Components::Position& pos, const Components::Size& size, bool intersect_with_current);


        static void ClipStartRounded(const Components::Position pos,
                                     const Components::Size size,
                                     Components::Rounding rounding) {

    const ::ImVec2 p0 = pos.ProperPosition.getImVec2();
    const ::ImVec2 sz = size.ProperSize.getImVec2();
    if (sz.x <= 0.0f || sz.y <= 0.0f)
        return;

    const ::ImVec2 p1 = ::ImVec2(p0.x + sz.x, p0.y + sz.y);
    const float w = sz.x;
    const float h = sz.y;
    const float rmax = ::ImMin(w, h) * 0.5f;

    const float tl_rounding = ::ImMin(rounding.properRounding.x, rmax);
    const float tr_rounding = ::ImMin(rounding.properRounding.y, rmax);
    const float bl_rounding = ::ImMin(rounding.properRounding.z, rmax);
    const float br_rounding = ::ImMin(rounding.properRounding.w, rmax);

    const ::ImVec2 c_tl = ::ImVec2(p0.x + tl_rounding, p0.y + tl_rounding);
    const ::ImVec2 c_tr = ::ImVec2(p1.x - tr_rounding, p0.y + tr_rounding);
    const ::ImVec2 c_bl = ::ImVec2(p0.x + bl_rounding, p1.y - bl_rounding);
    const ::ImVec2 c_br = ::ImVec2(p1.x - br_rounding, p1.y - br_rounding);

    ::ImDrawList* draw_list = ::ImGui::GetBackgroundDrawList();
    draw_list->AddCallback(StencilClipSetup, nullptr);

    draw_list->PathClear();

    if (tl_rounding > 0.0f)
        draw_list->PathArcTo(c_tl, tl_rounding, IM_PI * 1.0f, IM_PI * 1.5f, 10);
    else
        draw_list->PathLineTo(p0);
    draw_list->PathLineTo(::ImVec2(c_tr.x, p0.y));

    if (tr_rounding > 0.0f)
        draw_list->PathArcTo(c_tr, tr_rounding, IM_PI * 1.5f, IM_PI * 2.0f, 10);
    else
        draw_list->PathLineTo(::ImVec2(p1.x, p0.y));
    draw_list->PathLineTo(::ImVec2(p1.x, c_br.y));

    if (br_rounding > 0.0f)
        draw_list->PathArcTo(c_br, br_rounding, IM_PI * 0.0f, IM_PI * 0.5f, 10);
    else
        draw_list->PathLineTo(p1);
    draw_list->PathLineTo(::ImVec2(c_bl.x, p1.y));

    if (bl_rounding > 0.0f)
        draw_list->PathArcTo(c_bl, bl_rounding, IM_PI * 0.5f, IM_PI * 1.0f, 10);
    else
        draw_list->PathLineTo(::ImVec2(p0.x, p1.y));
    draw_list->PathLineTo(::ImVec2(p0.x, c_tl.y));

    draw_list->PathFillConvex(ImColor(0, 0, 0, 0));

    draw_list->AddCallback(StencilClipStartDraw, nullptr);
}

        static void ClipEndRounded()
        {
    ::ImDrawList* draw_list = ::ImGui::GetBackgroundDrawList();
    draw_list->AddCallback(StencilClipEnd, nullptr);
}


    };

}
