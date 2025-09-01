#include "Element.hpp"

namespace akairo
{
    std::shared_ptr<Renderer::Interface> Element::GetRenderer() const
    {
        return renderer;
    }
}
