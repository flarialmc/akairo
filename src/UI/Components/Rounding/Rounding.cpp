#include "Rounding.hpp"

namespace akairo::Components
{
    Rounding::Rounding()
    {
        this->TopLeft = 0.f;
        this->TopRight = 0.f;
        this->BottomLeft = 0.f;
        this->BottomRight = 0.f;
    }

    Rounding::Rounding(float r)
    {
        this->TopLeft = r;
        this->TopRight = r;
        this->BottomLeft = r;
        this->BottomRight = r;
    }

    Rounding::Rounding(float tl, float tr, float bl, float br)
    {
        this->TopLeft = tl;
        this->TopRight = tr;
        this->BottomLeft = bl;
        this->BottomRight = br;
    }
}
