#pragma once
#include <imgui.h>

class Vec2
{
public:
    float x, y;

    Vec2(float x = 0, float y = 0): x(x), y(y) {};

    Vec2 operator+(Vec2 vec2) const
    {
        return {this->x + vec2.x, this->y + vec2.y};
    }

    Vec2 operator-(Vec2 vec2) const
    {
        return {this->x - vec2.x, this->y - vec2.y};
    }

    Vec2 operator*(Vec2 vec2) const
    {
        return {this->x * vec2.x, this->y * vec2.y};
    }

    Vec2 operator*(float num) const
    {
        return {this->x * num, this->y * num};
    }

    Vec2 operator/(Vec2 vec2) const
    {
        return {this->x / vec2.x, this->y / vec2.y};
    }

    Vec2 operator/(float num) const
    {
        return {this->x / num, this->y / num};
    }

    [[nodiscard]] ImVec2 getImVec2() const
    {
        return {this->x, this->y};
    }
};
