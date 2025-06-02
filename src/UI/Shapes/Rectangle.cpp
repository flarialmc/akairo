#include "Rectangle.hpp"

#include <iostream>
#include <ostream>

namespace akairo::Shapes {
    Rectangle::Rectangle(const std::string& name, const Components::Position& position, const Components::Size& size, const std::shared_ptr<Renderer::Interface>& renderer, const Components::Color color)
    : Shape(name, position, size, color, renderer) {}

    Rectangle::Rectangle(const std::string& name, const std::shared_ptr<Renderer::Interface>& renderer): Shape(name, renderer)
    {
        this->Update({static_cast<float>(renderer->Width), static_cast<float>(renderer->Height)});
    }


    void Rectangle::Draw() {
        if (renderer) renderer->DrawRectangle(com_position, com_size, com_color, com_rounding);
        else std::cout << "Renderer is not set for Rectangle: " << name << std::endl;
    }

    void Rectangle::Update(Vec2 stuff)
    {
        BoundingRect ParentBounds = BoundingRect(this->com_position.ProperPosition, this->com_position.ProperPosition + stuff);
        this->com_position.Bind(ParentBounds);
        this->com_size.Bind(ParentBounds);

    }

    void Rectangle::Update()
    {
        if (parent)
        {
            const BoundingRect ParentBounds = BoundingRect(parent->com_position.ProperPosition, parent->com_position.ProperPosition + parent->com_size.ProperSize);

            this->com_position.Bind(ParentBounds);
            this->com_position.Bind(ParentBounds);
        }
        this->com_position.Update();
        this->com_size.Update();

        for (auto& child : children)
        {
            child->Update();
        }
    }
}

