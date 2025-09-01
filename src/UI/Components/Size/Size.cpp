#include "Size.hpp"

#include <iostream>
#include <ostream>

namespace akairo::Components
{
    Size::Size(Vec2 Size, BoundingRect Bounds, bool WidthDependsOnHeight)
    {
        this->WidthDependsOnHeight = WidthDependsOnHeight;
        constraints = Size;
        this->Bounds = Bounds;

        Vec2 Constraint = Vec2(Size.x, Size.y)/100.f;

        if (WidthDependsOnHeight)
        {
            size = Constraint * (Bounds.BottomRight - Bounds.TopLeft).y;
        }
        else
        {
            size = Constraint * (Bounds.BottomRight - Bounds.TopLeft);
        }
    }

    Size::Size()
    {
        this->size = Vec2();
        this->constraints = Vec2();
        this->Bounds = BoundingRect();
    }


    void Size::bind(const BoundingRect& Bounds)
    {
        this->Bounds = Bounds;
        update();
    }

    void Size::update()
    {
        Vec2 Constraint = Vec2(this->constraints.x, this->constraints.y)/100.f;

        if (WidthDependsOnHeight)
        {
            size = Constraint * (this->Bounds.BottomRight - this->Bounds.TopLeft).y;
        }
        else
        {
            size = Constraint * (this->Bounds.BottomRight - this->Bounds.TopLeft);
        }
    }

    void Size::update(Vec2 Size)
    {
        constraints = Size;
        Vec2 Constraint = Vec2(this->constraints.x, this->constraints.y)/100.f;

        if (WidthDependsOnHeight)
        {
            size = Constraint * (this->Bounds.BottomRight - this->Bounds.TopLeft).y;
        }
        else
        {
            size = Constraint * (this->Bounds.BottomRight - this->Bounds.TopLeft);
        }
    }
}
