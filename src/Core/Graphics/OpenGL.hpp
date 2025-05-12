#pragma once
#include "IGraphicsHandler.hpp"
#include <backends/imgui_impl_android.h>
#include <gl/GL.h>


namespace akairo::Graphics {
    class OpenGL : public IGraphicsHandler {
     public:
       OpenGL(int Width, int Height);
       ~OpenGL() override;
        bool Initialize(int Width, int Height);
        void Resize(int Width, int Height) override;
    };
};