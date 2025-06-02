#pragma once
#include <string>

namespace akairo::Components
{
    class Rounding
    {
    public:
        float TopLeft, TopRight, BottomLeft, BottomRight;

        Rounding();
        explicit Rounding(float r);
        Rounding(float tl, float tr, float bl, float br);
    };
}
