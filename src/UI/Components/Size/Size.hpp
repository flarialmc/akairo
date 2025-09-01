#pragma once
#include "Utils/BoundingRect.hpp"

namespace akairo::Components {
    class Size
    {
        bool WidthDependsOnHeight = true;
        BoundingRect Bounds;

    public:
        Vec2 constraints; //Size Constraints (eg Vec2(50, 60) => 50% from left and 60% from top
        Vec2 size; //Size In Pixels

        Size(Vec2 Size, BoundingRect ParentRect, bool WidthDependsOnHeight = true);
        Size();
        void bind(const BoundingRect& Bounds);
        void update();
        void update(Vec2 Size);
    };
}
