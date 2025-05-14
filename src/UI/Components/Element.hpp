#pragma once
#include <memory>
#include <vector>
#include <string>

#include "Size.hpp"
#include "../../Core/Renderer/ImGui.hpp"

/*
 * Each element is given a name.
 * It will have a parent to derive sizes from.
 * It will have children to affect it's sizes
 * It will have a designated renderer holding the base screen resolution sizes, etc.
 *
 * There may be changes in the future.
 */

namespace akairo::Components
{
    class Element
    {
    public:
        virtual ~Element() = default;
        Element(std::string name, std::unique_ptr<Renderer::Interface> renderer)
            : name(std::move(name)), renderer(std::move(renderer)) {}

        void AddChild(std::unique_ptr<Element> child); //Adds child to the list
        void RemoveChild(std::unique_ptr<Element> child); //Removes child
        void Parentize(std::unique_ptr<Element> Parent); //Changes the parent or adds the parent to this element
        void Update();

    private:
        std::string name;
        std::unique_ptr<Element> parent = nullptr;
        std::vector<std::unique_ptr<Element>> children;
        std::unique_ptr<Renderer::Interface> renderer;

        Position position;
        Size size;
    };
}
