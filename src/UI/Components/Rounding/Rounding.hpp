#pragma once
#include <string>
#include <Utils/Vectors.hpp>

namespace akairo::Components
{
    class Rounding
    {
    public:
        Vec4 roundingConstraints;
        Vec4 properRounding;
        int scaler;

        Rounding(int scaler);
        Rounding(float r, int scaler);
        Rounding(Vec4 r, int scaler);

        void Update(int scaler);
    };
}
