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
    class FlexibleContainer : public Element{
    public:
        FlexibleContainer(std::string name, const std::shared_ptr<Renderer::Interface>& renderer, const std::shared_ptr<Element>& body);
        ~FlexibleContainer() override;

        bool sterile = true;

        std::shared_ptr<Element> _body;
        Vec4 _padding;
        Vec2 _gap;
        CONTAINER_FLEX_DIRECTION _direction;
        CONTAINER_FLEX_BEHAVIOR _flexBehavior;
        CONTAINER_OVERFLOW_BEHAVIOR _overflowBehavior;

        auto body(this auto& self, std::shared_ptr<Element> x) {
            self._body = std::move(x);
            using T = std::remove_cvref_t<decltype(self)>;
            return std::static_pointer_cast<T>(self.shared_from_this());
        }

        auto padding(this auto& self, Vec4 padding) {
            self._padding = padding;
            using T = std::remove_cvref_t<decltype(self)>;
            return std::static_pointer_cast<T>(self.shared_from_this());
        }

        auto gap(this auto& self, Vec2 gap) {
            self._gap = gap;
            using T = std::remove_cvref_t<decltype(self)>;
            return std::static_pointer_cast<T>(self.shared_from_this());
        }

        auto direction(this auto& self, CONTAINER_FLEX_DIRECTION direction) {
            self._direction = direction;
            using T = std::remove_cvref_t<decltype(self)>;
            return std::static_pointer_cast<T>(self.shared_from_this());
        }

        auto flexBehavior(this auto& self, CONTAINER_FLEX_BEHAVIOR behavior) {
            self._flexBehavior = behavior;
            using T = std::remove_cvref_t<decltype(self)>;
            return std::static_pointer_cast<T>(self.shared_from_this());
        }

        auto overflowBehavior(this auto& self, CONTAINER_OVERFLOW_BEHAVIOR behavior) {
            self._overflowBehavior = behavior;
            using T = std::remove_cvref_t<decltype(self)>;
            return std::static_pointer_cast<T>(self.shared_from_this());
        }


        void remove(const std::string& name);

        void draw() override;
        void updateInternal(const Vec2& contentStart, const Vec2& contentSize) const;
        void update() override;
        void update(Vec2 newbounds) override;
    };
}
