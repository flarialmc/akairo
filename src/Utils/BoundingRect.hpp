#pragma once
#include "Vectors.hpp"

class BoundingRect
{
public:
    Vec2 TopLeft; //In Pixels
    Vec2 TopRight; //In Pixels
    Vec2 BottomLeft; //In Pixels
    Vec2 BottomRight; //In Pixels
};