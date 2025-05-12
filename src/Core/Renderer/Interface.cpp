#include "Interface.hpp"


bool akairo::Renderer::Interface::Initialize()
{
    if (this->Backend == UndefinedBackend) return false;

    if (this->Framework == UndefinedFramework) return false;

    return true;
}