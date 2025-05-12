#include "Renderer.hpp"

Renderer::Renderer(Backends backend, Frameworks framework)
{
    this->Backend = backend;
    this->Framework = framework;
}

bool Renderer::Initialize()
{
    if (this->Backend == UndefinedBackend) return false; //Backend not defined.

    if (this->Framework == UndefinedFramework) return false; //Framework not defined

    switch (this->Framework)
    {
    case ImGUI:  this->InitializeImGUI();
    }


    return true;
}

bool Renderer::InitializeImGUI()
{

    switch (this->Backend)
    {
    case OPENGL: this->InitializeImGUIOpenGL(); // ImGui OpenGL3 Initialization
    case DIRECTX11: this->InitializeImGUIDx11(); // ImGui DirectX11 Initialization
    }

    return true;
}

bool Renderer::InitializeImGUIOpenGL()
{
    return true;
}

bool Renderer::InitializeImGUIDx11()
{
    return true;
}