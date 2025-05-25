#pragma once
#include "Interface.hpp"

namespace akairo::Graphics {
    class OpenGL : public Interface {
     public:
       OpenGL(int Width, int Height);
    };
};