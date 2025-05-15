#include "Rectangle.hpp"

namespace akairo::Shapes {
    Rectangle::Rectangle(std::string name, const Components::Position& position, Components::Size size,
            std::unique_ptr<Renderer::Interface> renderer)
        : Shape(std::move(name), position, size, std::move(renderer)) {
    }

    void Rectangle::Draw() {
        auto Renderer = GetRenderer();
        if (Renderer) {
            Renderer->DrawRectangle(position, size);
        }
    }

    void Rectangle::Update() {
        // Basic update implementation
    }
}
