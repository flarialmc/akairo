#pragma once
#include <string>
#include <Utils/Vectors.hpp>

namespace akairo::Components
{
    class Rounding
    {
    public:
        Vec4 constraints;
        Vec4 rounding;
        int scaler;

        explicit Rounding(int scaler);
        Rounding(float r, int scaler);
        Rounding(Vec4 r, int scaler);

        void update(int scaler);
    };
}
