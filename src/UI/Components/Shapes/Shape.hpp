#pragma once
#include <utility>

#include "Element.hpp"
#include "Position.hpp"

namespace akairo::Shapes {
    class Shape : public Components::Element {
    public:
        Components::Position position{};
        //Components::Size size; COMING SOON!
        //Components::Color color; COMING SOON!

        virtual void Update() = 0;

        Shape(const Components::Position& position,
            std::string name,
            std::unique_ptr<Renderer::Interface> renderer)

        : Element(std::move(name), std::move(renderer)),

        position(position) {}


    };
}
