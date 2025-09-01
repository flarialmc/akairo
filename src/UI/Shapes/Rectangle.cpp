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
        this->Update({static_cast<float>(renderer->Width), static_cast<float>(renderer->Height)});
    }


    void Rectangle::Draw() {
        if (renderer)
        {
            renderer->DrawRectangle(_position, _size, com_color, com_rounding);
            if (_clip) renderer->PushClipRect(_position, _size, true);

            for (const std::shared_ptr<Element>& x : children)
            {
                x->Draw();
            }

            if (_clip) renderer->PopClipRect();
        }
        else std::cout << "Renderer is not set for Rectangle: " << name << std::endl;
    }

    void Rectangle::Update(Vec2 newbounds)
    {
        if (auto parent = this->parent.lock())
        {
            const auto ParentBounds = BoundingRect(parent->_position.position, parent->_position.position + parent->_size.size);
            this->_position.Bind(ParentBounds);
            this->_size.Bind(ParentBounds);
        } else
        {
            BoundingRect ParentBounds = BoundingRect({0, 0}, newbounds);
            this->_position.Bind(ParentBounds);
            this->_size.Bind(ParentBounds);
        }
        this->com_rounding.Update(this->renderer->Height);

        for (auto& child : children)
        {
            child->Update();
        }
    }

    void Rectangle::Update()
    {
        if (auto parent = this->parent.lock())
        {
            const auto ParentBounds = BoundingRect(parent->_position.position, parent->_position.position + parent->_size.size);
            this->_position.Bind(ParentBounds);
            this->_size.Bind(ParentBounds);
        }
        this->_position.Update();
        this->_size.Update();
        this->com_rounding.Update(this->renderer->Height);

        for (auto& child : children)
        {
            child->Update();
        }
    }
}