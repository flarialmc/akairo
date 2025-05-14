#include "Color.hpp"

akairo::Components::Color::Color(float r, float g, float b, float a)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

akairo::Components::Color::Color(int r, int g, int b, int a)
{
    this->r = r / 255;
    this->g = g / 255;
    this->b = b / 255;
    this->a = a / 255;
}

akairo::Components::Color::Color()
{
    this->r = this->g = this->b = this->a = 0;
}
