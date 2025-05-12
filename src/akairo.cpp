#include "akairo.hpp"

bool akairo::CreateRenderer(const std::string& name, Renderer::Backends RendererBackend, Renderer::Frameworks RendererFramework) {
    if (renderers[name])
    {
        return false; //There's already a Renderer with the same identifier.
    }

    renderers[name] = new Renderer(RendererBackend, RendererFramework);

    return true; //Successfully created a new Renderer.
}

Renderer* akairo::GetRenderer(const std::string& name)
{
    return renderers[name]; //Return the renderer
}