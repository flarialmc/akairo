#pragma once
#include "Shape.hpp"

namespace akairo::Shapes {
    class Rectangle : public Shape {
    public:
        Rectangle(const Components::Position& position, Components::Size size, std::unique_ptr<Renderer::Interface> renderer, Components::Color color);
        void Draw() override;
    };
}