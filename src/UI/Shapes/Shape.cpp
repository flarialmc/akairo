#include "Shape.hpp"

akairo::Shapes::Shape::Shape(const Components::Position& position, Components::Size size, Components::Color color, std::shared_ptr<Renderer::Interface> renderer)
{
    this->position = position;
    this->size = size;
    this->color = color;
    this->renderer = renderer;
}

void akairo::Shapes::Shape::UpdateShape(const Components::Position& position, Components::Size size, Components::Color color, std::shared_ptr<Renderer::Interface> renderer)
{
    this->position = position;
    this->size = size;
    this->color = color;
    this->renderer = renderer;
}
