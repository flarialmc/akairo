#include "Size.hpp"

#include <iostream>
#include <ostream>

namespace akairo::Components
{
    Size::Size(Vec2 Size, BoundingRect Bounds, bool WidthDependsOnHeight)
    {
        this->WidthDependsOnHeight = WidthDependsOnHeight;
        SizeConstraints = Size;
        this->Bounds = Bounds;

        Vec2 Constraint = Vec2(Size.x, Size.y)/100.f;

        if (WidthDependsOnHeight)
        {
            ProperSize = Constraint * (Bounds.BottomRight - Bounds.TopLeft).y;
        }
        else
        {
            ProperSize = Constraint * (Bounds.BottomRight - Bounds.TopLeft);
        }
    }

    Size::Size()
    {
        this->WidthDependsOnHeight = false;
        this->ProperSize = Vec2();
        this->SizeConstraints = Vec2();
        this->Bounds = BoundingRect();
    }


    void Size::Bind(const BoundingRect& Bounds)
    {
        this->Bounds = Bounds;
        Update();
    }

    void Size::Update()
    {
        Vec2 Constraint = Vec2(this->SizeConstraints.x, this->SizeConstraints.y)/100.f;

        if (WidthDependsOnHeight)
        {
            ProperSize = Constraint * (this->Bounds.BottomRight - this->Bounds.TopLeft).y;
        }
        else
        {
            ProperSize = Constraint * (this->Bounds.BottomRight - this->Bounds.TopLeft);
        }
        std::cout << "Size updated to: " << ProperSize.x << ", " << ProperSize.y << std::endl;
    }

    void Size::Update(Vec2 Size)
    {
        SizeConstraints = Size;
        Vec2 Constraint = Vec2(this->SizeConstraints.x, this->SizeConstraints.y)/100.f;

        if (WidthDependsOnHeight)
        {
            ProperSize = Constraint * (this->Bounds.BottomRight - this->Bounds.TopLeft).y;
        }
        else
        {
            ProperSize = Constraint * (this->Bounds.BottomRight - this->Bounds.TopLeft);
        }
    }
}
