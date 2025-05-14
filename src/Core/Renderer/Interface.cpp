#include "Interface.hpp"


bool akairo::Renderer::Interface::Initialize() const
{
    if (this->backendType == UndefinedBackend) return false;

    return true;
}
