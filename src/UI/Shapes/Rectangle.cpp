#include "Rectangle.hpp"

#include <iostream>
#include <ostream>

#include "Core/Renderer/ImGui.hpp"

namespace akairo::Shapes
{
    Rectangle::Rectangle(const std::string& name, const Components::Position& position, const Components::Size& size, const std::shared_ptr<Renderer::Interface>& renderer, const Components::Color color)
    : Shape(name, position, size, color, renderer) {}

    Rectangle::Rectangle(const std::string& name, const std::shared_ptr<Renderer::Interface>& renderer): Shape(name, renderer)
    {
        this->update({static_cast<float>(renderer->Width), static_cast<float>(renderer->Height)});
    }


    void Rectangle::draw() {
        if (renderer)
        {
            renderer->DrawRectangle(_position, _size, _color, _rounding);
            if (_clip) renderer->PushClipRect(_position, _size, true);

            for (const std::shared_ptr<Element>& x : children)
            {
                x->draw();
            }

            if (_clip) renderer->PopClipRect();
        }
        else std::cout << "Renderer is not set for Rectangle: " << name << std::endl;
    }

    void Rectangle::update(Vec2 newbounds)
    {
        if (auto parent = this->parent.lock())
        {
            const auto ParentBounds = BoundingRect(parent->_position.position, parent->_position.position + parent->_size.size);
            this->_position.bind(ParentBounds);
            this->_size.bind(ParentBounds);
        } else
        {
            BoundingRect ParentBounds = BoundingRect({0, 0}, newbounds);
            this->_position.bind(ParentBounds);
            this->_size.bind(ParentBounds);
        }
        this->_rounding.update(this->renderer->Height);

        for (auto& child : children)
        {
            child->update();
        }
    }

    void Rectangle::update()
    {
        if (auto parent = this->parent.lock())
        {
            const auto ParentBounds = BoundingRect(parent->_position.position, parent->_position.position + parent->_size.size);
            this->_position.bind(ParentBounds);
            this->_size.bind(ParentBounds);
        }
        this->_position.update();
        this->_size.update();
        this->_rounding.update(this->renderer->Height);

        for (auto& child : children)
        {
            child->update();
        }
    }
}