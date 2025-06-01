#pragma once
#include <iostream>
#include <memory>
#include <ostream>
#include <utility>
#include <vector>
#include <string>

#include "Components/Size/Size.hpp"
#include "Core/Renderer/Interface.hpp"

/*
 * Each element is given a name.
 * It will have a parent to derive sizes from.
 * It will have children to affect it's sizes
 * It will have a designated renderer holding the base screen resolution sizes, etc.
 *
 * There may be changes in the future.
 */

namespace akairo
{

    namespace Renderer
    {
        class Interface;
    };

    class Element
    {
    public:
        virtual ~Element() = default;

        Element(std::string name, const std::shared_ptr<Renderer::Interface>& renderer)
            : name(std::move(name)), renderer(renderer)
        {
            this->renderer = renderer;
        }

        void AddChild(std::shared_ptr<Element> child);
        void RemoveChild(const std::shared_ptr<Element>& child);
        void Bind(std::shared_ptr<Element> Parent);
        virtual void Update() {};
        virtual void Update(Vec2 stuff) {};
        virtual void Draw() = 0;
        [[nodiscard]] std::shared_ptr<Renderer::Interface> GetRenderer() const;

        std::string name;
        std::shared_ptr<Element> parent = nullptr;
        std::vector<std::shared_ptr<Element>> children;
        std::shared_ptr<Renderer::Interface> renderer;

        Components::Position com_position;
        Components::Size com_size;

        bool Drawable = false;

        Element& position(const Vec2 pos) {
            this->com_position.Update(pos);
            return *this;
        }

        Element& size(const Vec2 size)
        {
            this->com_size.Update(size);
            return *this;

        }

        Element&  width(const float width)
        {
            this->com_size.Update(Vec2(width, this->com_size.SizeConstraints.y));
            return *this;
        }

        Element& height(const float height)
        {
            this->com_size.Update(Vec2(this->com_size.SizeConstraints.x, height));
            return *this;
        }
    };
}
