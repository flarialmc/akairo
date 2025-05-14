#pragma once
#include "Vectors.hpp"

class BoundingRect
{
public:
    Vec2 TopLeft; //In Pixels
    Vec2 TopRight; //In Pixels
    Vec2 BottomLeft; //In Pixels
    Vec2 BottomRight; //In Pixels

    BoundingRect()
    {
        this->TopLeft = Vec2();
        this->TopRight = Vec2();
        this->BottomLeft = Vec2();
        this->BottomRight = Vec2();
    }

    BoundingRect(Vec2 TopLeft, Vec2 TopRight, Vec2 BottomLeft, Vec2 BottomRight)
    {
        this->TopLeft = TopLeft;
        this->TopRight = TopRight;
        this->BottomLeft = BottomLeft;
        this->BottomRight = BottomRight;
    }

    BoundingRect(Vec2 TopLeft, Vec2 BottomRight)
    {
        this->TopLeft = TopLeft;
        this->TopRight = Vec2(BottomRight.x, TopLeft.y);
        this->BottomLeft = Vec2(TopLeft.x, BottomRight.y);
        this->BottomRight = BottomRight;
    }
};