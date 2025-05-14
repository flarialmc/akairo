#pragma once
#include "Shape.hpp"

namespace akairo::Shapes {
    class Rectangle : public Shape {
    public:
        Rectangle(const Components::Position& position,
                 std::string name,
                 std::unique_ptr<Renderer::Interface> renderer);

        void Draw() override;
        void Update() override;
    };
}