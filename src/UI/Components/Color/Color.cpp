#include "Color.hpp"

namespace akairo::Components
{
    Color::Color(float r, float g, float b, float a)
    {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }

    Color::Color(int r, int g, int b, int a)
    {
        this->r = r / 255;
        this->g = g / 255;
        this->b = b / 255;
        this->a = a / 255;
    }

    Color::Color()
    {
        this->r = this->g = this->b = this->a = 0;
    }

    Color::Color(const std::string& hex, int a) {
        const char* ptr = hex.c_str();

        // Skip '#' if present
        if (*ptr == '#') ++ptr;

        auto hexToInt = [](char c) -> int {
            return (c <= '9') ? (c - '0') : ((c | 32) - 'a' + 10);
        };

        const int rInt = (hexToInt(ptr[0]) << 4) | hexToInt(ptr[1]);
        const int gInt = (hexToInt(ptr[2]) << 4) | hexToInt(ptr[3]);
        const int bInt = (hexToInt(ptr[4]) << 4) | hexToInt(ptr[5]);

        constexpr float inv255 = 1.0f / 255.0f;
        r = rInt * inv255;
        g = gInt * inv255;
        b = bInt * inv255;
        this->a = a * inv255;
    }

    ImColor Color::toImColor() const
    {
        return {r, g, b, a};
    }
}
