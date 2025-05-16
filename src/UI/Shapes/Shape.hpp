#pragma once
#include <utility>

#include "Core/Renderer/Interface.hpp"
#include "UI/Components/Color/Color.hpp"
namespace akairo
{
    namespace Renderer
    {
        class Interface;
    }
}

namespace akairo::Shapes {
    class Shape {
    public:

        Components::Position position;
        Components::Size size;
        Components::Color color;
        std::unique_ptr<Renderer::Interface> renderer;

        virtual void Draw() = 0;

        Shape(const Components::Position& position, Components::Size size, Components::Color color, std::unique_ptr<Renderer::Interface> renderer);
        void UpdateShape(const Components::Position& position, Components::Size size, Components::Color color, std::unique_ptr<Renderer::Interface> renderer);


    };
}
