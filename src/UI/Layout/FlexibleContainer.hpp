#pragma once
#include <utility>

#include "UI/Element.hpp"
#define FLEX_CONTAINER(name, renderer, body) \
std::make_shared<akairo::Layouts::FlexibleContainer>(name, renderer, body)

/*
 * Enumeration to determine which direction the elements will arrange in.
 */
enum CONTAINER_FLEX_DIRECTION {
    TOP_TO_BOTTOM,
    BOTTOM_TO_TOP,
    LEFT_TO_RIGHT,
    RIGHT_TO_LEFT,
};

enum CONTAINER_FLEX_BEHAVIOR
{
    NOWRAP,
    WRAP,
};

enum CONTAINER_OVERFLOW_BEHAVIOR {
    HIDDEN, /* Clips out of bound elements */
    VISIBLE, /* Allows elements to be visible */
    SCROLL, /* Turns it into a scrollable page */
    ENLARGE /* Automatically enlarges itself depending on the elements inside */
};



/*
 * This behaves like a CSS flexbox.
 * Elements will grow in accordance to Container itself.
 * You can define the dimension in which you want the elements to arrange in, vertical or horizontal.
 * it automatically positions the elements according to the direction, the only thing you must define is a size.
 * There can be a Container inside of a Container!
 * TO DO: padding, auto sizing of elements
 */
namespace akairo::Layouts {
    class FlexibleContainer final : public Element, public std::enable_shared_from_this<FlexibleContainer> {
    public:
        FlexibleContainer(std::string name, const std::shared_ptr<Renderer::Interface>& renderer, const std::shared_ptr<Element>& body);
        ~FlexibleContainer() override;

        std::shared_ptr<Element> _body;
        Vec4 _padding;
        Vec2 _gap;
        CONTAINER_FLEX_DIRECTION _direction;
        CONTAINER_FLEX_BEHAVIOR _flexBehavior;
        CONTAINER_OVERFLOW_BEHAVIOR _overflowBehavior;

        std::shared_ptr<FlexibleContainer> body(std::shared_ptr<Element> x)
        {
            this->_body = std::move(x);
            return shared_from_this();
        }

        std::shared_ptr<FlexibleContainer> padding(Vec4 padding)
        {
            this->_padding = padding;
            return shared_from_this();
        }

        std::shared_ptr<FlexibleContainer> gap(Vec2 gap)
        {
            this->_gap = gap;
            return shared_from_this();
        }

        std::shared_ptr<FlexibleContainer> direction(CONTAINER_FLEX_DIRECTION direction)
        {
            this->_direction = direction;
            return shared_from_this();
        }

        std::shared_ptr<FlexibleContainer> flexBehavior(CONTAINER_FLEX_BEHAVIOR behavior)
        {
            this->_flexBehavior = behavior;
            return shared_from_this();
        }

        std::shared_ptr<FlexibleContainer> overflowBehavior(CONTAINER_OVERFLOW_BEHAVIOR behavior)
        {
            this->_overflowBehavior = behavior;
            return shared_from_this();
        }


        template<typename... Elems>
        std::shared_ptr<FlexibleContainer> add(const std::shared_ptr<Element>& first, Elems&&... rest) {
            children.push_back(first);
            (children.push_back(std::forward<Elems>(rest)), ...); // fold expression
            return shared_from_this();
        }
        void remove(const std::string& name);

        void Draw() override;
        void UpdateInternal(const Vec2& contentStart, const Vec2& contentSize) const;
        void Update() override;
        void Update(Vec2 newbounds) override;
    };
}
