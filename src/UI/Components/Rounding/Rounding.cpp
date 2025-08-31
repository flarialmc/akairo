#include "Rounding.hpp"

#include <iostream>

#include "Utils/Vectors.hpp"

namespace akairo::Components
{
    Rounding::Rounding(int scaler)
    {
        this->scaler = scaler;
        this->properRounding.x = 0.f;
        this->properRounding.y = 0.f;
        this->properRounding.z = 0.f;
        this->properRounding.w = 0.f;

        this->roundingConstraints.x = 0.0f;
        this->roundingConstraints.y = 0.0f;
        this->roundingConstraints.z = 0.0f;
        this->roundingConstraints.w = 0.0f;
    }

    Rounding::Rounding(float r, int scaler)
    {
        this->scaler = scaler;
        this->properRounding.x = r / 100.f * scaler;
        this->properRounding.y = r / 100.f * scaler;
        this->properRounding.z = r / 100.f * scaler;
        this->properRounding.w = r / 100.f * scaler;

        this->roundingConstraints.x = r;
        this->roundingConstraints.y = r;
        this->roundingConstraints.z = r;
        this->roundingConstraints.w = r;
    }

    Rounding::Rounding(Vec4 r, int scaler)
    {
        this->scaler = scaler;
        this->properRounding.x = r.x / 100.f * scaler;
        this->properRounding.y = r.y / 100.f * scaler;
        this->properRounding.z = r.z / 100.f * scaler;
        this->properRounding.w = r.w / 100.f * scaler;

        this->roundingConstraints.x = r.x;
        this->roundingConstraints.y = r.y;
        this->roundingConstraints.z = r.z;
        this->roundingConstraints.w = r.w;
    }

    void Rounding::Update(int scaler) {
        this->scaler = scaler;
        this->properRounding.x = this->roundingConstraints.x / 100.f * scaler;
        this->properRounding.y = this->roundingConstraints.y / 100.f * scaler;
        this->properRounding.z = this->roundingConstraints.z / 100.f * scaler;
        this->properRounding.w = this->roundingConstraints.w / 100.f * scaler;
    }

}
