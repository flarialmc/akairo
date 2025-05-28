#pragma once
#include "Shape.hpp"

namespace akairo::Shapes {
    class Rectangle final : public Shape {
    public:
        Rectangle(const std::string& name, const Components::Position& position, const Components::Size& size, const std::shared_ptr<Renderer::Interface>& renderer, Components::Color color);
        void Draw() override;
    };
}