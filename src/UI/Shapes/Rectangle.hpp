#pragma once
#include <UI/Components/Rounding/Rounding.hpp>

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
        Components::Rounding com_rounding = {0.f, 0};
        Rectangle(const std::string& name, const Components::Position& position, const Components::Size& size, const std::shared_ptr<Renderer::Interface>& renderer, Components::Color color);
        Rectangle(const std::string& name, const std::shared_ptr<Renderer::Interface>& renderer);
        void Draw() override;
        void Update() override;
        void Update(Vec2 stuff) override;

        Rectangle& position(const Vec2 constraints) override
        {
            this->com_position.Update(constraints);
            return *this;
        }

        Rectangle& size(const Vec2 size) override {
            this->com_size.Update(size);
            return *this;
        }

        Rectangle& width(const float w) override {
            this->com_size.Update(Vec2(w, this->com_size.SizeConstraints.y));
            return *this;
        }

        Rectangle& height(const float h) override {
            this->com_size.Update(Vec2(this->com_size.SizeConstraints.x, h));
            return *this;
        }

        Rectangle& color(const std::string& hex, const int alpha) override {
            this->com_color = Components::Color(hex, alpha);
            return *this;
        }

        Rectangle& color(const int r, const int g, const int b, const int a) override {
            this->com_color = Components::Color(r, g, b, a);
            return *this;
        }

        Rectangle& rounding(const float r, const int scaler) {
            this->com_rounding = Components::Rounding(r, scaler);
            return *this;
        }

        Rectangle& rounding(const float tl, const float tr, const float bl, const float br, const int scaler) {
            this->com_rounding = Components::Rounding(Vec4(tl, tr, bl, br), scaler);
            return *this;
        }

        std::shared_ptr<Rectangle> build()
        {
            return std::make_shared<Rectangle>(*this);
        }

    };
}