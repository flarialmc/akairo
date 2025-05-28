#include "Rectangle.hpp"

#include <iostream>
#include <ostream>

namespace akairo::Shapes {
    Rectangle::Rectangle(const std::string& name, const Components::Position& position, const Components::Size& size, const std::shared_ptr<Renderer::Interface>& renderer, const Components::Color color)
    : Shape(name, position, size, color, renderer) {}

    void Rectangle::Draw() {
        if (renderer) renderer->DrawRectangle(position, size, color);
        else std::cout << "Renderer is not set for Rectangle: " << name << std::endl;
    }
}
