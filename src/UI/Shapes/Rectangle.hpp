#pragma once
#include "Shape.hpp"

namespace akairo::Shapes {
    class Rectangle : public Shape {
    public:
        Rectangle(std::string name, const Components::Position& position, Components::Size size,
            std::unique_ptr<Renderer::Interface> renderer);

        void Draw() override;
        void Update() override;
    };
}