#include "Element.hpp"

namespace akairo
{
    void Element::AddChild(std::shared_ptr<Element> child)
    {
        children.push_back(std::move(child));
    }

    void Element::RemoveChild(const std::shared_ptr<Element>& child)
    {
        std::erase(children, child);
    }

    void Element::Parentize(std::shared_ptr<Element> Parent)
    {
        this->parent = std::move(Parent);
    }

    void Element::Update()
    {
        const BoundingRect ParentBounds = BoundingRect(parent->position.ProperPosition, parent->position.ProperPosition + parent->size.ProperSize);

        this->position.Parentize(ParentBounds);
        this->size.Bind(ParentBounds);
        this->size.Update();
        this->position.Update();

        for (auto& child : children)
        {
            child->Update();
        }
    }

    std::shared_ptr<Renderer::Interface> Element::GetRenderer() const
    {
        return renderer;
    }
}
