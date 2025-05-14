#pragma once
#include "../../Utils/Vectors.hpp"
#include "../../Utils/BoundingRect.hpp"

namespace akairo::Components {
    class Size
    {
        bool WidthDependsOnHeight = false;
        BoundingRect Parent;

    public:
        Vec2 SizeConstraints; //Size Constraints (eg Vec2(50, 60) => 50% from left and 60% from top
        Vec2 ProperSize; //Size In Pixels

        Size(Vec2 Size, BoundingRect ParentRect, bool WidthDependsOnHeight = false);
        void Parentize(BoundingRect ParentRect);
        void Update();
        void Update(Vec2 Size);
    };
}