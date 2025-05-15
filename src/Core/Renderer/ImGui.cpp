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

    void ImGui::DrawRectangle(Components::Position pos) const
    {

        // add Size soon
    }
}
