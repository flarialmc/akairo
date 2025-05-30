#include "Position.hpp"

akairo::Components::Position::Position(Vec2 Position, BoundingRect ParentRect)
{

    PositionConstraints = Position;

    Vec2 Constraint = Vec2(PositionConstraints.x, PositionConstraints.y)/100.f;

    RelativePosition = Constraint * (ParentRect.BottomRight - ParentRect.TopLeft);

    ProperPosition = RelativePosition;
}

akairo::Components::Position::Position()
{
    this->RelativePosition = Vec2();
    this->ProperPosition = Vec2();
    this->RelativePosition = Vec2();
    this->Parent = BoundingRect();
}


void akairo::Components::Position::Parentize(BoundingRect ParentRect)
{
    this->Parent = ParentRect;
    Update();
}

void akairo::Components::Position::Update()
{
    Vec2 Constraint = Vec2(PositionConstraints.x, PositionConstraints.y)/100.f;

    RelativePosition = Constraint * (Parent.BottomRight - Parent.TopLeft);

    ProperPosition = RelativePosition;
}

void akairo::Components::Position::Update(Vec2 Position)
{
    PositionConstraints = Position;

    Vec2 Constraint = Vec2(Position.x, Position.y)/100.f;

    RelativePosition = Constraint * (Parent.BottomRight - Parent.TopLeft);

    ProperPosition = RelativePosition;
}
