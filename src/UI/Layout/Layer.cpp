//
// Created by Rifat on 8/25/2025.
//

#include "Layer.hpp"

#include <iostream>
#include <ostream>
#include <utility>

namespace akairo::Layouts
{
    Layer::Layer(std::string name, const std::shared_ptr<Renderer::Interface>& renderer)
    : Element(std::move(name), renderer) {};

    Layer::~Layer()
    = default;

    void Layer::update()
    {
        for (auto e : children)
        {
            e->update();
        }
    }

    void Layer::update(Vec2 newbounds)
    {
        for (auto e : children)
        {
            e->update(newbounds);
        }
    }

    void Layer::draw()
    {

        for (auto e : children)
        {
            e->draw();
        }
    }

};
