#pragma once

#include "Core/Renderer/Interface.hpp"
#include "UI/Element.hpp"
namespace akairo::Renderer
{
    class Interface;
}
namespace akairo
{
    class Element;
}

namespace akairo::Shapes {
    class Shape : public Element{
    public:
        ~Shape() override = default;

        Shape(std::string name, const Components::Position& position, const Components::Size& size, Components::Color color, const std::shared_ptr<Renderer::Interface>& renderer);
        explicit Shape(const std::string& name, const std::shared_ptr<Renderer::Interface>& renderer);
        void UpdateShape(const Components::Position& position, const Components::Size& size, Components::Color color, std::shared_ptr<Renderer::Interface> renderer);

        Components::Color com_color = {};
    };
}
