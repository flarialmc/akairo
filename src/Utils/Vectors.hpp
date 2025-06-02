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

class Vec3 {
public:
    float x, y, z;

    Vec3(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}

    Vec3 operator+(const Vec3& v) const {
        return {x + v.x, y + v.y, z + v.z};
    }

    Vec3 operator-(const Vec3& v) const {
        return {x - v.x, y - v.y, z - v.z};
    }

    Vec3 operator*(const Vec3& v) const {
        return {x * v.x, y * v.y, z * v.z};
    }

    Vec3 operator*(float n) const {
        return {x * n, y * n, z * n};
    }

    Vec3 operator/(const Vec3& v) const {
        return {x / v.x, y / v.y, z / v.z};
    }

    Vec3 operator/(float n) const {
        return {x / n, y / n, z / n};
    }
};

class Vec4 {
public:
    float x, y, z, w;

    Vec4(float x = 0, float y = 0, float z = 0, float w = 0) : x(x), y(y), z(z), w(w) {}

    Vec4 operator+(const Vec4& v) const {
        return {x + v.x, y + v.y, z + v.z, w + v.w};
    }

    Vec4 operator-(const Vec4& v) const {
        return {x - v.x, y - v.y, z - v.z, w - v.w};
    }

    Vec4 operator*(const Vec4& v) const {
        return {x * v.x, y * v.y, z * v.z, w * v.w};
    }

    Vec4 operator*(float n) const {
        return {x * n, y * n, z * n, w * n};
    }

    Vec4 operator/(const Vec4& v) const {
        return {x / v.x, y / v.y, z / v.z, w / v.w};
    }

    Vec4 operator/(float n) const {
        return {x / n, y / n, z / n, w / n};
    }
};