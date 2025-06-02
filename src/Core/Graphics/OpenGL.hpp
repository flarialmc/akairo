#pragma once
#include "Interface.hpp"

namespace akairo::Graphics {
    class OpenGL : public Interface {
     public:
       OpenGL(int Width, int Height);
       ~OpenGL() override;
       bool Initialize(int Width, int Height) override;
       void Shutdown() override;
       void Resize(int Width, int Height) override;
    };
};