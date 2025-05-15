#pragma once
#include <utility>

#include "Core/Renderer/Interface.hpp"
#include "UI/Element.hpp"
#include "UI/Components/Color/Color.hpp"


namespace akairo::Shapes {
    class Shape : public Element {
    public:

        Components::Position position;
        Components::Size size;
        Components::Color color;

        virtual void Draw() = 0;

        Shape(std::string name, const Components::Position& position, Components::Size size,
            std::unique_ptr<Renderer::Interface> renderer)

        : Element(std::move(name), std::move(renderer)),

        position(position) {}


    };
}
