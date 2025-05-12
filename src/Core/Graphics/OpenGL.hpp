#pragma once
#include <gl/GL.h>
#include <cassert>
#include <windef.h>
#include "IGraphicsHandler.hpp"

namespace Graphics {
    class OpenGL : public IGraphicsHandler {
     HDC hwnd;

     public:
       OpenGL();
       ~OpenGL();
       bool Initialize() override;


    };
};