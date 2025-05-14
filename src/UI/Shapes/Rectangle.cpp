#include "Rectangle.hpp"
#include "Renderer/Interface.hpp"

namespace akairo::Shapes {
    Rectangle::Rectangle(const Components::Position& position,
                       std::string name,
                       std::unique_ptr<Renderer::Interface> renderer)
        : Shape(position, std::move(name), std::move(renderer)) {
    }

    void Rectangle::Draw() {
        auto Renderer = GetRenderer();
        if (Renderer) {
            Renderer->DrawRectangle(position); // Add size later
        }
    }

    void Rectangle::Update() {
        // Basic update implementation
    }
}
