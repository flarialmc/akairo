#include "ImGui.hpp"

/*
 * There is no need to call an initializer as "initialization" is conducted inside the constructor.
 */

akairo::Renderer::ImGui::ImGui(BackendType backend, int Width, int Height): Interface(backend), io()
{
    this->backend = std::make_unique<Graphics::OpenGL>(Width, Height);
    this->backendType = backend;

    switch (backend)
    {
        case BackendType::OpenGL: { ImGui_ImplOpenGL3_Init("#version 300 es"); }
        default: {}
    }

    this->context = ::ImGui::CreateContext();
    this->io = ::ImGui::GetIO();
    this->list = ::ImGui::GetBackgroundDrawList();
}
