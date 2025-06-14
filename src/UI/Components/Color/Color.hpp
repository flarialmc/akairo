#pragma once
#include <imgui.h>
#include <string>

namespace akairo::Components
{
class Color
{
public:
    float r, g, b, a;

    Color(float r, float g, float b, float a);
    Color(int r, int g, int b, int a);
    Color(const std::string& hex, int a);
    Color();

    ImColor toImColor() const;
};
}
