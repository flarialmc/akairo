#pragma once
#include <memory>
#include <UI/Components/Rounding/Rounding.hpp>
#include "Shape.hpp"
#include <algorithm>

#define RECTANGLE(name, renderer) \
std::make_shared<akairo::Shapes::Rectangle>(name, renderer)

namespace akairo::Shapes {
    class Rectangle final : public Shape, public std::enable_shared_from_this<Rectangle> {
    public:
        Components::Rounding com_rounding = { 0.f, 0 };

        Rectangle(
            const std::string& name,
            const Components::Position& position,
            const Components::Size& size,
            const std::shared_ptr<Renderer::Interface>& renderer,
            Components::Color color
        );
        Rectangle(const std::string& name, const std::shared_ptr<Renderer::Interface>& renderer);

        void Draw() override;
        void Update() override;
        void Update(Vec2 newbounds) override;

        /*
         * Builder system (used to return Rectangle&)
         */

        std::shared_ptr<Rectangle> position(const Vec2 constraints) 
        {
            this->com_position.Update(constraints);
            return shared_from_this();
        }

        std::shared_ptr<Rectangle> size(const Vec2 size)
        {
            this->com_size.Update(size);
            return shared_from_this();
        }

        std::shared_ptr<Rectangle> width(const float w)
        {
            this->com_size.Update(Vec2(w, this->com_size.SizeConstraints.y));
            return shared_from_this();
        }

        std::shared_ptr<Rectangle> height(const float h)
        {
            this->com_size.Update(Vec2(this->com_size.SizeConstraints.x, h));
            return shared_from_this();
        }

        std::shared_ptr<Rectangle> color(const std::string& hex, const int alpha)
        {
            this->com_color = Components::Color(hex, alpha);
            return shared_from_this();
        }

        std::shared_ptr<Rectangle> color(const int r, const int g, const int b, const int a)
        {
            this->com_color = Components::Color(r, g, b, a);
            return shared_from_this();
        }

        std::shared_ptr<Rectangle> rounding(const float r)
        {
            this->com_rounding = Components::Rounding(r, this->renderer->Width);
            return shared_from_this();
        }

        std::shared_ptr<Rectangle> rounding(const float tl, const float tr, const float bl, const float br)
        {
            this->com_rounding = Components::Rounding(Vec4(tl, tr, bl, br), this->renderer->Width);
            return shared_from_this();
        }

        std::shared_ptr<Rectangle> visible(const bool r)
        {
            this->Visible = r;
            return shared_from_this();
        }

        std::shared_ptr<Rectangle> clip(const bool r)
        {
            this->Clip = r;
            return shared_from_this();
        }

        std::shared_ptr<Rectangle> movable(const bool r)
        {
            this->Movable = r;
            return shared_from_this();
        }

        std::shared_ptr<Rectangle> scrollable(const bool r)
        {
            this->Scrollable = r;
            return shared_from_this();
        }


        std::shared_ptr<Rectangle> addChild(std::shared_ptr<Element> child)
        {
            auto this_ = shared_from_this();
            child->parent = this_;
            children.push_back(std::move(child));

            return this_;
        }

        std::shared_ptr<Rectangle> removeChild(const std::shared_ptr<Element>& child)
        {
            children.erase(std::remove(children.begin(), children.end(), child), children.end());
            return shared_from_this();
        }
    };
}
