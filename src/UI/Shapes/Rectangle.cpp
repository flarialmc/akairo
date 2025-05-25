#include "Rectangle.hpp"

namespace akairo::Shapes {
    Rectangle::Rectangle(const Components::Position& position, Components::Size size, std::unique_ptr<Renderer::Interface> renderer, Components::Color color)
    : Shape(position, size, color, std::move(renderer)) {}

    void Rectangle::Draw() {
        auto Renderer = std::move(renderer);
        if (Renderer) {
            Renderer->DrawRectangle(position, size, color);
        }
    }
}
