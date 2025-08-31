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
            renderer->DrawRectangle(com_position, com_size, com_color, com_rounding);
            auto r = dynamic_cast<Renderer::ImGui*>(renderer.get());
            if (Clip && r) r->PushClipRect(com_position, com_size, true);

            for (const std::shared_ptr<Element>& x : children)
            {
                x->Draw();
            }
            if (Clip && r) r->PopClipRect();
        }
        else std::cout << "Renderer is not set for Rectangle: " << name << std::endl;
    }

    void Rectangle::Update(Vec2 newbounds)
    {
        if (auto parent = this->parent.lock())
        {
            const auto ParentBounds = BoundingRect(parent->com_position.ProperPosition, parent->com_position.ProperPosition + parent->com_size.ProperSize);
            this->com_position.Bind(ParentBounds);
            this->com_size.Bind(ParentBounds);
        } else
        {
            BoundingRect ParentBounds = BoundingRect({0, 0}, newbounds);
            this->com_position.Bind(ParentBounds);
            this->com_size.Bind(ParentBounds);
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
            const auto ParentBounds = BoundingRect(parent->com_position.ProperPosition, parent->com_position.ProperPosition + parent->com_size.ProperSize);
            this->com_position.Bind(ParentBounds);
            this->com_size.Bind(ParentBounds);
        }
        this->com_position.Update();
        this->com_size.Update();
        this->com_rounding.Update(this->renderer->Height);

        for (auto& child : children)
        {
            child->Update();
        }
    }
}