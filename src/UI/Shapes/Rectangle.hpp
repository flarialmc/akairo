#pragma once
#include <memory>
#include <UI/Components/Rounding/Rounding.hpp>
#include "Shape.hpp"
#include <algorithm>

#define RECTANGLE(name, renderer) \
std::make_shared<akairo::Shapes::Rectangle>(name, renderer)

namespace akairo::Shapes {
    class Rectangle final : public Shape {
    public:
        Components::Rounding _rounding = { 0.f, 0 };

        Rectangle(
            const std::string& name,
            const Components::Position& position,
            const Components::Size& size,
            const std::shared_ptr<Renderer::Interface>& renderer,
            Components::Color color
        );
        Rectangle(const std::string& name, const std::shared_ptr<Renderer::Interface>& renderer);

        void draw() override;
        void update() override;
        void update(Vec2 newbounds) override;

        /*
         * Builder system (used to return Rectangle&)
         */

        std::shared_ptr<Rectangle> rounding(const float r)
        {
            this->_rounding = Components::Rounding(r, this->renderer->Width);
            return std::static_pointer_cast<Rectangle>(shared_from_this());
        }

        std::shared_ptr<Rectangle> rounding(const float tl, const float tr, const float bl, const float br)
        {
            this->_rounding = Components::Rounding(Vec4(tl, tr, bl, br), this->renderer->Width);
            return std::static_pointer_cast<Rectangle>(shared_from_this());
        }

    };
}
