#include "Element.hpp"

void akairo::Components::Element::AddChild(std::unique_ptr<Element> child)
{
    children.push_back(std::move(child));
}

void akairo::Components::Element::RemoveChild(std::unique_ptr<Element> child)
{
    children.erase(std::remove(children.begin(), children.end(), child), children.end());
}

void akairo::Components::Element::Parentize(std::unique_ptr<Element> Parent)
{
    this->parent = std::move(Parent);
}

void akairo::Components::Element::Update()
{
    const BoundingRect ParentBounds = BoundingRect(parent->position.ProperPosition, parent->position.ProperPosition + parent->size.ProperSize);

    this->position.Parentize(ParentBounds);
    this->size.Parentize(ParentBounds);

    for (auto& child : children)
    {
        child->Update();
    }
}
