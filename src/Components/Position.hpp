#pragma once
#include <imgui.h>
#include "../Utils/Vectors.hpp"
#include "../Utils/BoundingRect.hpp"

namespace akairo::Components {
class Position
{
    Vec2 PositionConstraints; //Position Constraints (eg Vec2(50, 60) => 50% from left and 60% from top
    Vec2 RelativePosition; //Position Relative to the Parent Rect (In Pixels)
    Vec2 ProperPosition; //RelativePosition + ParentRect Position

    Position(Vec2 Position, BoundingRect ParentRect)
    {

        PositionConstraints = Position;

        Vec2 Constraint = Vec2(Position.x, Position.y)/100.f;

        RelativePosition = Constraint * (ParentRect.BottomRight - ParentRect.TopLeft);

        ProperPosition = RelativePosition + ParentRect.TopLeft;
    }
};
}