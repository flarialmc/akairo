#pragma once
#include "Utils/BoundingRect.hpp"

namespace akairo::Components {
    class Size
    {
        bool WidthDependsOnHeight = true;
        BoundingRect Bounds;

    public:
        Vec2 SizeConstraints; //Size Constraints (eg Vec2(50, 60) => 50% from left and 60% from top
        Vec2 ProperSize; //Size In Pixels

        Size(Vec2 Size, BoundingRect ParentRect, bool WidthDependsOnHeight = true);
        Size();
        void Bind(const BoundingRect& Bounds);
        void Update();
        void Update(Vec2 Size);
    };
}
