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

    void Layer::Update()
    {
        for (auto e : elements)
        {
            e.second->Update();
        }
    }

    void Layer::Update(Vec2 newbounds)
    {
        for (auto e : elements)
        {
            e.second->Update(newbounds);
        }
    }

    void Layer::Draw()
    {
        for (auto it = this->elements.begin(); it != this->elements.end(); ++it)
        {
            it->second->Draw();
        }
    }

};
