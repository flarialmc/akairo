#pragma once
#include "Interface.hpp"

namespace akairo::Graphics {
    class OpenGL : public Interface {
     public:
       OpenGL(int Width, int Height);
       ~OpenGL();
       bool Initialize(int Width, int Height);
       void Shutdown();
    };
};