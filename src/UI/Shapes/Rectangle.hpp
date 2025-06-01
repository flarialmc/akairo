#pragma once
#include "Shape.hpp"

namespace akairo::Shapes {
    class Rectangle final : public Shape {
    public:

        /*
         * In the future, have a different constructor that takes in just the constraint values for each component.
         * And a hex perhaps, for the color.
         * It would look something like this:
         * Rectangle(const std::string& name, Vec2 position, Vec2 size, const std::shared_ptr<Renderer::Interface>& renderer, const std::string& hexColor);
         * Or maybe, move to a builder system for better readability and usability.
         */
        Rectangle(const std::string& name, const Components::Position& position, const Components::Size& size, const std::shared_ptr<Renderer::Interface>& renderer, Components::Color color);
        Rectangle(const std::string& name, const std::shared_ptr<Renderer::Interface>& renderer);
        void Draw() override;
        void Update() override;
        void Update(Vec2 stuff) override;
        std::shared_ptr<Rectangle> build()
        {
            return std::make_shared<Rectangle>(*this);
        }

    };
}