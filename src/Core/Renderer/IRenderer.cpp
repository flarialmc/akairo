#include "IRenderer.hpp"

IRenderer::IRenderer(BackendType backend, FrameworkType framework)
{
    this->Backend = backend;
    this->Framework = framework;
}

bool IRenderer::Initialize()
{
    if (this->Backend == UndefinedBackend) return false;

    if (this->Framework == UndefinedFramework) return false;

    switch (this->Framework)
    {
    case ImGUI:  this->InitializeImGUI();
    }


    return true;
}