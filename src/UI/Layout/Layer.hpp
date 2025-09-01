#pragma once
#include <complex.h>

#include "UI/Element.hpp"
#include "UI/Shapes/Rectangle.hpp"

/*
 * This is a basic layer.
 * Put any element of your choosing on this, to nicely organize your pages.
 * For example: mainhud, settings menu, chat menu, etc.
 */

#define LAYER(name, renderer) \
std::make_shared<akairo::Layouts::Layer>(name, renderer)

namespace akairo::Layouts
{
    class Layer final : public Element
    {
        std::map<std::string, std::shared_ptr<Element>> elements;
    public:
        Layer(std::string name, const std::shared_ptr<Renderer::Interface>& renderer);
        ~Layer() override;

        bool sterile = true;

        void draw() override;
        void update() override;
        void update(Vec2 newbounds) override;
    };
}
