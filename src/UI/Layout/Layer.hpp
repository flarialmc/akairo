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
    class Layer final : public Element, public std::enable_shared_from_this<Layer>
    {
        std::map<std::string, std::shared_ptr<Element>> elements;
    public:
        Layer(std::string name, const std::shared_ptr<Renderer::Interface>& renderer);
        ~Layer() override;

        std::shared_ptr<Layer> add(const std::shared_ptr<Element>& element)
        {
            this->elements[element->name] = element;
            return shared_from_this();
        }
        std::shared_ptr<Layer> remove(const std::shared_ptr<Element>& element)
        {
            this->elements.erase(element->name);
            return shared_from_this();
        }
        std::shared_ptr<Layer> modify(const std::shared_ptr<Element>& element)
        {
            this->elements[element->name] = element;
            return shared_from_this();
        }

        void Draw() override;
        void Update() override;
        void Update(Vec2 newbounds) override;
    };
}
