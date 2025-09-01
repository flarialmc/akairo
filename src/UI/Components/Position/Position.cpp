#include "Position.hpp"

#include <iostream>

akairo::Components::Position::Position(Vec2 Position, BoundingRect ParentRect)
{

    constraints = Position;

    Vec2 Constraint = Vec2(constraints.x, constraints.y)/100.f;

    relativePosition = Constraint * (ParentRect.BottomRight - ParentRect.TopLeft);

    position = Parent.TopLeft + relativePosition;
}

akairo::Components::Position::Position()
{
    this->relativePosition = Vec2();
    this->position = Vec2();
    this->relativePosition = Vec2();
    this->Parent = BoundingRect();
}


void akairo::Components::Position::Bind(BoundingRect ParentRect)
{
    this->Parent = ParentRect;
    Update();
}

void akairo::Components::Position::Update()
{
    Vec2 Constraint = Vec2(constraints.x, constraints.y)/100.f;
    relativePosition = Constraint * (Parent.BottomRight - Parent.TopLeft);

    position = Parent.TopLeft + relativePosition;
}

void akairo::Components::Position::Update(Vec2 Position)
{
    constraints = Position;

    Vec2 Constraint = Vec2(Position.x, Position.y)/100.f;

    relativePosition = Constraint * (Parent.BottomRight - Parent.TopLeft);

    position = Parent.TopLeft + relativePosition;
}
