#include "ImGui.hpp"
akairo::Renderer::ImGui::ImGui(BackendType backend, int Width, int Height): Interface(backend)
{
    this->OpenGL = std::make_unique<Graphics::OpenGL>(Width, Height);
    this->context = ::ImGui::CreateContext();
    this->io = &::ImGui::GetIO();
    ImGui_ImplOpenGL3_Init("#version 300 es");
}
