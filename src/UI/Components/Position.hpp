#pragma once
#include <imgui.h>
#include "../../Utils/Vectors.hpp"
#include "../../Utils/BoundingRect.hpp"

namespace akairo::Components {
    class Position
    {
        Vec2 PositionConstraints; //Position Constraints (eg Vec2(50, 60) => 50% from left and 60% from top
        Vec2 RelativePosition; //Position Relative to the Parent Rect (In Pixels)
        Vec2 ProperPosition; //RelativePosition + ParentRect Position

    public:
        explicit Position(const Vec2 Position, BoundingRect ParentRect = {})
        {
            PositionConstraints = Position;
            Vec2 Constraint = Vec2(Position.x, Position.y)/100.f;

            RelativePosition = Constraint * (ParentRect.BottomRight - ParentRect.TopLeft);

            ProperPosition = RelativePosition + ParentRect.TopLeft;

        }

        void UpdateFromParent(BoundingRect ParentRect)
        {
            Vec2 Constraint = Vec2(PositionConstraints.x, PositionConstraints.y)/100.f;

            RelativePosition = Constraint * (ParentRect.BottomRight - ParentRect.TopLeft);

            ProperPosition = RelativePosition + ParentRect.TopLeft;
        }

        Vec2 Get() const
        {
            return ProperPosition;
        }
    };
}