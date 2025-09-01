#pragma once
#include <imgui.h>

#include "Utils/BoundingRect.hpp"
#include "Utils/Vectors.hpp"

namespace akairo::Components {
class Position
{

    BoundingRect Parent;

public:
    Vec2 constraints; //Position Constraints (eg Vec2(50, 60) => 50% from left and 60% from top
    Vec2 relativePosition; //Position Relative to the Parent Rect (In Pixels)
    Vec2 position; //relativePosition + ParentRect Position

    explicit Position(Vec2 Position, BoundingRect ParentRect = {});
    Position();
    void bind(BoundingRect ParentRect);
    void update();
    void update(Vec2 Position);
};
}
