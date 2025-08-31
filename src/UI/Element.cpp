#include "Element.hpp"

namespace akairo
{


    void Element::Bind(std::shared_ptr<Element> Parent)
    {
        this->parent = std::move(Parent);
    }

    std::shared_ptr<Renderer::Interface> Element::GetRenderer() const
    {
        return renderer;
    }
}
