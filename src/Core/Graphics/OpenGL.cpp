
#include "OpenGL.hpp"

// TODO:
// in the future, after talking with White
// i should try to add EGLSuraface, etc. Android specific, Windows specific, etc.
namespace akairo::Graphics
{
    OpenGL::OpenGL(int Width, int Height)
    {
        this->Width = Width;
        this->Height = Height;
    }

    OpenGL::~OpenGL()
    {
        OpenGL::Shutdown();
    }

    bool OpenGL::Initialize(int Width, int Height)
    {
        this->Width = Width;
        this->Height = Height;
        // TODO: Add OpenGL initialization code
        return true;
    }

    void OpenGL::Shutdown()
    {
        // TODO: Add OpenGL cleanup code
    }
}
