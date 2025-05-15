#pragma once
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

    Position(Vec2 Position, BoundingRect ParentRect = {});
    Position();
    void Parentize(BoundingRect ParentRect);
    void Update();
    void Update(Vec2 Position);
};
}
