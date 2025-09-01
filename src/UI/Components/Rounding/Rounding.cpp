#include "Rounding.hpp"

#include <iostream>

#include "Utils/Vectors.hpp"

namespace akairo::Components
{
    Rounding::Rounding(int scaler)
    {
        this->scaler = scaler;
        this->rounding.x = 0.f;
        this->rounding.y = 0.f;
        this->rounding.z = 0.f;
        this->rounding.w = 0.f;

        this->constraints.x = 0.0f;
        this->constraints.y = 0.0f;
        this->constraints.z = 0.0f;
        this->constraints.w = 0.0f;
    }

    Rounding::Rounding(float r, int scaler)
    {
        this->scaler = scaler;
        this->rounding.x = r / 100.f * scaler;
        this->rounding.y = r / 100.f * scaler;
        this->rounding.z = r / 100.f * scaler;
        this->rounding.w = r / 100.f * scaler;

        this->constraints.x = r;
        this->constraints.y = r;
        this->constraints.z = r;
        this->constraints.w = r;
    }

    Rounding::Rounding(Vec4 r, int scaler)
    {
        this->scaler = scaler;
        this->rounding.x = r.x / 100.f * scaler;
        this->rounding.y = r.y / 100.f * scaler;
        this->rounding.z = r.z / 100.f * scaler;
        this->rounding.w = r.w / 100.f * scaler;

        this->constraints.x = r.x;
        this->constraints.y = r.y;
        this->constraints.z = r.z;
        this->constraints.w = r.w;
    }

    void Rounding::Update(int scaler) {
        this->scaler = scaler;
        this->rounding.x = this->constraints.x / 100.f * scaler;
        this->rounding.y = this->constraints.y / 100.f * scaler;
        this->rounding.z = this->constraints.z / 100.f * scaler;
        this->rounding.w = this->constraints.w / 100.f * scaler;
    }

}
