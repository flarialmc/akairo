#pragma once
#include <imgui.h>

#include "Utils/BoundingRect.hpp"
#include "Utils/Vectors.hpp"

namespace akairo::Components {
class Position
{

    BoundingRect Parent;

public:
    Vec2 PositionConstraints; //Position Constraints (eg Vec2(50, 60) => 50% from left and 60% from top
    Vec2 RelativePosition; //Position Relative to the Parent Rect (In Pixels)
    Vec2 ProperPosition; //RelativePosition + ParentRect Position

    explicit Position(Vec2 Position, BoundingRect ParentRect = {});
    Position();
    void Bind(BoundingRect ParentRect);
    void Update();
    void Update(Vec2 Position);
};
}
