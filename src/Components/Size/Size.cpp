#include "Size.hpp"

akairo::Components::Size::Size(Vec2 Size, BoundingRect ParentRect, bool WidthDependsOnHeight)
{
    this->WidthDependsOnHeight = WidthDependsOnHeight;
    SizeConstraints = Size;
    this->Parent = ParentRect;

    Vec2 Constraint = Vec2(Size.x, Size.y)/100.f;

    if (WidthDependsOnHeight)
    {
        ProperSize = Constraint * (ParentRect.BottomRight - ParentRect.TopLeft).y;
    }
    else
    {
        ProperSize = Constraint * (ParentRect.BottomRight - ParentRect.TopLeft);
    }
}

void akairo::Components::Size::Parentize(BoundingRect ParentRect)
{
    this->Parent = ParentRect;
    Update();
}

void akairo::Components::Size::Update()
{
    Vec2 Constraint = Vec2(this->SizeConstraints.x, this->SizeConstraints.y)/100.f;

    if (WidthDependsOnHeight)
    {
        ProperSize = Constraint * (this->Parent.BottomRight - this->Parent.TopLeft).y;
    }
    else
    {
        ProperSize = Constraint * (this->Parent.BottomRight - this->Parent.TopLeft);
    }
}

void akairo::Components::Size::Update(Vec2 Size)
{
    SizeConstraints = Size;
    Vec2 Constraint = Vec2(this->SizeConstraints.x, this->SizeConstraints.y)/100.f;

    if (WidthDependsOnHeight)
    {
        ProperSize = Constraint * (this->Parent.BottomRight - this->Parent.TopLeft).y;
    }
    else
    {
        ProperSize = Constraint * (this->Parent.BottomRight - this->Parent.TopLeft);
    }
}
