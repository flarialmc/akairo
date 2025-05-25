#pragma once
#include <memory>
#include <vector>
#include <string>

#include "Components/Size/Size.hpp"
#include "Shapes/Shape.hpp"
#include "Core/Renderer/Interface.hpp"

/*
 * Each element is given a name.
 * It will have a parent to derive sizes from.
 * It will have children to affect it's sizes
 * It will have a designated renderer holding the base screen resolution sizes, etc.
 *
 * There may be changes in the future.
 */

namespace akairo
{
    namespace Renderer
    {
        class Interface;
    }

    namespace Shapes
    {
        class Shape;
    }

    class Element
    {
    public:
        virtual ~Element() = default;
        Element(std::string name, Renderer::Interface* renderer)
            : name(std::move(name)), renderer(renderer) {}

        void AddChild(std::unique_ptr<Element> child); //Adds child to the list
        void RemoveChild(std::unique_ptr<Element> child); //Removes child
        void Parentize(std::unique_ptr<Element> Parent); //Changes the parent or adds the parent to this element
        template <typename ShapeType, typename... TArgs>
        void SetShape(TArgs... argList)
        {
            shape = std::unique_ptr<ShapeType>(position, size, renderer, std::forward<TArgs>(argList)...);
            Drawable = true;
        }
        virtual void Update();

        Renderer::Interface* GetRenderer();

        std::string name;
        std::unique_ptr<Element> parent = nullptr;
        std::vector<std::unique_ptr<Element>> children;
        Renderer::Interface* renderer;

        Components::Position position;
        Components::Size size;

        bool Drawable = false;
        std::unique_ptr<Shapes::Shape> shape = nullptr;

    };
}
