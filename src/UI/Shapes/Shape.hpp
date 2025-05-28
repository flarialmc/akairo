#pragma once
#include <utility>

#include "Core/Renderer/Interface.hpp"
#include "UI/Components/Color/Color.hpp"

    namespace akairo::Renderer
    {
        class Interface;
    }


namespace akairo::Shapes {
    class Shape : public Element {
    public:
        ~Shape() override = default;

        Components::Position position;
        Components::Size size;
        Components::Color color;
        std::shared_ptr<Renderer::Interface> renderer;

        virtual void Draw() = 0;

        Shape(std::string name, const Components::Position& position, const Components::Size& size, Components::Color color, const std::shared_ptr<Renderer::Interface>& renderer);
        void UpdateShape(const Components::Position& position, const Components::Size& size, Components::Color color, std::shared_ptr<Renderer::Interface> renderer);


    };
}
