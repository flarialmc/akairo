#pragma once
#include <utility>

#include "../../Element.hpp"
#include "Color/Color.hpp"

namespace akairo::Shapes {
    class Shape : public Components::Element {
    public:
        Components::Position position;
        Components::Size size;
        Components::Color color;

        virtual void Draw() = 0;

        Shape(const Components::Position& position,
            std::string name,
            std::unique_ptr<Renderer::Interface> renderer)

        : Element(std::move(name), std::move(renderer)),

        position(position) {}


    };
}
