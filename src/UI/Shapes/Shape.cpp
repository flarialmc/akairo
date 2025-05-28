#include "Shape.hpp"

#include <utility>

akairo::Shapes::Shape::Shape(std::string name, const Components::Position& position, const Components::Size& size, const Components::Color color, const std::shared_ptr<Renderer::Interface>& renderer):
    Element(std::move(name), renderer)
{
    this->position = position;
    this->size = size;
    this->color = color;
}

void akairo::Shapes::Shape::UpdateShape(const Components::Position& position, const Components::Size& size, const Components::Color color, std::shared_ptr<Renderer::Interface> renderer)
{
    this->position = position;
    this->size = size;
    this->color = color;
    this->renderer = std::move(renderer);
}
