#include "Rectangle.hpp"

#include <utility>

namespace akairo::Shapes {
    Rectangle::Rectangle(const Components::Position& position, const Components::Size& size, std::shared_ptr<Renderer::Interface> renderer, const Components::Color color)
    : Shape(position, size, color, std::move(renderer)) {}

    void Rectangle::Draw() {
        if (const auto Renderer = renderer) {
            Renderer->DrawRectangle(position, size, color);
        }
    }
}
