#pragma once
#include <iostream>
#include <memory>
#include <utility>
#include <vector>
#include <string>


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

    class Element : public std::enable_shared_from_this<Element>
    {
    public:
        virtual ~Element() = default;

        Element(std::string name, const std::shared_ptr<Renderer::Interface>& renderer)
            : name(std::move(name)), renderer(renderer) {}

        /*
         * Call this function once you've modified the attributes of your Element,
         * such as position, size, rounding, etc.
         */
        virtual void update() {};

        /*
         * This function is called by Graphics to update every element
         * letting them to resize due to window size change.
         */
        virtual void update(Vec2 newbounds) { };

        /*
         * Draws the element! Duh.
         */
        virtual void draw() = 0;
        [[nodiscard]] std::shared_ptr<Renderer::Interface> GetRenderer() const;

        std::string name;
        bool sterile = false; /* To ensure Components don't break in things like FlexibleContainer, Layer.. */

        /*
        * Accessing the parent will be like:
        * if (auto p = parent.lock()) // p is a shared_ptr
        */
        std::weak_ptr<Element> parent;
        std::vector<std::shared_ptr<Element>> children;
        std::shared_ptr<Renderer::Interface> renderer;

        template <typename... Elems>
        auto addChild(this auto& self, const std::shared_ptr<Element>& first, Elems&&... rest) {
            auto setParent = [&](const std::shared_ptr<Element>& child) {
                if (!self.sterile) child->parent = self.shared_from_this();
                self.children.push_back(child);
            };

            setParent(first);
            (setParent(std::forward<Elems>(rest)), ...);

            using T = std::remove_cvref_t<decltype(self)>;
            return std::static_pointer_cast<T>(self.shared_from_this());
        }

        auto removeChild(this auto& self, const std::shared_ptr<Element>& child) {
            auto it = std::find(self.children.begin(), self.children.end(), child);
            if (it != self.children.end()) {
                (*it)->parent.reset();
                self.children.erase(it);
            }

            using T = std::remove_cvref_t<decltype(self)>;
            return std::static_pointer_cast<T>(self.shared_from_this());
        }


        /* Components */

        Components::Position _position;
        Components::Size _size;

        auto position(this auto& self, Vec2 constraints) {
            self._position.update(constraints);
            using T = std::remove_cvref_t<decltype(self)>;
            return std::static_pointer_cast<T>(self.shared_from_this());
        }

        auto size(this auto& self, Vec2 sz) {
            self._size.update(sz);
            using T = std::remove_cvref_t<decltype(self)>;
            return std::static_pointer_cast<T>(self.shared_from_this());
        }

        auto width(this auto& self, float w) {
            self._size.update(Vec2(w, self._size.constraints.y));
            using T = std::remove_cvref_t<decltype(self)>;
            return std::static_pointer_cast<T>(self.shared_from_this());
        }

        auto height(this auto& self, float h) {
            self._size.update(Vec2(self._size.constraints.x, h));
            using T = std::remove_cvref_t<decltype(self)>;
            return std::static_pointer_cast<T>(self.shared_from_this());
        }


        /* Basic Attributes */
        bool _movable = false;
        bool _scrollable = false;
        bool _clip = false;
        bool _visible = true;

        auto visible(this auto& self, bool r) {
            self._visible = r;
            using T = std::remove_cvref_t<decltype(self)>;
            return std::static_pointer_cast<T>(self.shared_from_this());
        }

        auto clip(this auto& self, bool r) {
            self._clip = r;
            using T = std::remove_cvref_t<decltype(self)>;
            return std::static_pointer_cast<T>(self.shared_from_this());
        }

        auto movable(this auto& self, bool r) {
            self._movable = r;
            using T = std::remove_cvref_t<decltype(self)>;
            return std::static_pointer_cast<T>(self.shared_from_this());
        }

        auto scrollable(this auto& self, bool r) {
            self._scrollable = r;
            using T = std::remove_cvref_t<decltype(self)>;
            return std::static_pointer_cast<T>(self.shared_from_this());
        }
    };
}
