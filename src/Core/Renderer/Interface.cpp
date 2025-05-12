#include "Interface.hpp"


bool akairo::Renderer::Interface::Initialize()
{
    if (this->backend == UndefinedBackend) return false;

    return true;
}