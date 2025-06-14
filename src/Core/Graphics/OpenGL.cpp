
#include "OpenGL.hpp"

#include <akairo.hpp>
#include <UI/Element.hpp>

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
    void OpenGL::Resize(int Width, int Height)
    {
        this->Width = Width;
        this->Height = Height;
        for (auto& r : renderers)
        {
            r.second->Width = Width;
            r.second->Height = Height;
            for (auto& [name, element] : r.second->elements)
            {
                if (!element->parent)
                {
                    element->Update(Vec2(Width, Height));
                }
            }

            for (auto& [name, element] : r.second->elements)
            {
                if (element->parent)
                {
                    element->Update();
                }
            }
        }
    }


}
