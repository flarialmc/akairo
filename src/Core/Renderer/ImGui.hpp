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
        void DrawRectangle(Components::Position pos, Components::Size size, Components::Color color, Components::Rounding rounding) const override;
        void DrawHollowRectangle(Components::Position pos, Components::Size size, Components::Color color, float Width) const override;
        void DrawCircle(Components::Position pos, float radius, Components::Color color) const override;
        void Render(const std::function<void()>& extra) override;
        void PushClipRect(const Components::Position& pos, const Components::Size& size, bool intersect_with_current) override;
        void PopClipRect() override;
    };

}
