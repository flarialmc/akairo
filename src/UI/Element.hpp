#pragma once
#include <iostream>
#include <memory>
#include <utility>
#include <vector>
#include <string>


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
    };

    class Element
    {
    public:
        virtual ~Element() = default;

        Element(std::string name, const std::shared_ptr<Renderer::Interface>& renderer)
            : name(std::move(name)), renderer(renderer) {}


        void Bind(std::shared_ptr<Element> Parent);

        /*
         * Call this function once you've modified the attributes of your Element,
         * such as position, size, rounding, etc.
         */
        virtual void Update() {};

        /*
         * This function is called by Graphics to update every element
         * letting them to resize due to window size change.
         */
        virtual void Update(Vec2 newbounds) { };

        /*
         * Draws the element! Duh.
         */
        virtual void Draw() = 0;
        [[nodiscard]] std::shared_ptr<Renderer::Interface> GetRenderer() const;



        std::string name;

        /*
        * Accessing the parent will be like:
        * if (auto p = parent.lock()) // p is a shared_ptr
        */
        std::weak_ptr<Element> parent;
        std::vector<std::shared_ptr<Element>> children;
        std::shared_ptr<Renderer::Interface> renderer;

        Components::Position com_position;
        Components::Size com_size;

        /* Basic Attributes */
        bool Movable = false;
        bool Scrollable = false;
        bool Clip = false;
        bool Visible = false;
    };
}
