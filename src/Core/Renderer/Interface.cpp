#include "Interface.hpp"


bool akairo::Renderer::Interface::Initialize()
{
    if (this->Backend == UndefinedBackend) return false;

    if (this->Framework == UndefinedFramework) return false;

    switch (this->Framework)
    {
    case ImGUI:  this->InitializeImGUI();
    default: ;
    }


    return true;
}