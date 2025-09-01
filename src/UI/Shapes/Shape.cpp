#include "Shape.hpp"

#include <utility>

namespace akairo::Shapes
{
    Shape::Shape(std::string name, const Components::Position& position, const Components::Size& size, const Components::Color color, const std::shared_ptr<Renderer::Interface>& renderer):
        Element(std::move(name), renderer)
    {
        this->_position = position;
        this->_size = size;
        this->_color = color;
    }
    Shape::Shape(const std::string& name, const std::shared_ptr<Renderer::Interface>& renderer): Element(name, renderer)
    {
        this->name = name;
    }

    void Shape::updateShape(const Components::Position& position, const Components::Size& size, const Components::Color color, std::shared_ptr<Renderer::Interface> renderer)
    {
        this->_position = position;
        this->_size = size;
        this->_color = color;
        this->renderer = std::move(renderer);
    }
}
