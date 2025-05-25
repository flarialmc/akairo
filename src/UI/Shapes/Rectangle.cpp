#include "Rectangle.hpp"

namespace akairo::Shapes {
    Rectangle::Rectangle(const Components::Position& position, Components::Size size, Renderer::Interface* renderer, Components::Color color)
    : Shape(position, size, color, renderer) {}

    void Rectangle::Draw() {
        auto Renderer = renderer;
        if (Renderer) {
            Renderer->DrawRectangle(position, size, color);
        }
    }
}
