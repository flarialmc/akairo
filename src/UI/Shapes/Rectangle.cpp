#include "Rectangle.hpp"

#include <utility>

namespace akairo::Shapes {
    Rectangle::Rectangle(const std::string& name, const Components::Position& position, const Components::Size& size, const std::shared_ptr<Renderer::Interface>& renderer, const Components::Color color)
    : Shape(name, position, size, color, renderer) {}

    void Rectangle::Draw() {
        if (const auto Renderer = renderer) {
            Renderer->DrawRectangle(position, size, color);
        }
    }
}
