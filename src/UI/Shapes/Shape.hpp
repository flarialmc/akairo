#pragma once

#include "Core/Renderer/Interface.hpp"
#include "UI/Element.hpp"
namespace akairo::Renderer
{
    class Interface;
}
namespace akairo
{
    class Element;
}

namespace akairo::Shapes {
    class Shape : public Element{
    public:
        ~Shape() override = default;

        Shape(std::string name, const Components::Position& position, const Components::Size& size, Components::Color color, const std::shared_ptr<Renderer::Interface>& renderer);
        explicit Shape(const std::string& name, const std::shared_ptr<Renderer::Interface>& renderer);
        void updateShape(const Components::Position& position, const Components::Size& size, Components::Color color, std::shared_ptr<Renderer::Interface> renderer);

        Components::Color _color = {};

        auto color(this auto& self, const std::string& hex, int alpha) {
            self._color = Components::Color(hex, alpha);
            using T = std::remove_cvref_t<decltype(self)>;
            return std::static_pointer_cast<T>(self.shared_from_this());
        }

        auto color(this auto& self, int r, int g, int b, int a) {
            self._color = Components::Color(r, g, b, a);
            using T = std::remove_cvref_t<decltype(self)>;
            return std::static_pointer_cast<T>(self.shared_from_this());
        }

    };
}
