
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
            std::cout << "Resizing renderer: " << r.first << " to " << Width << "x" << Height << std::endl;
            for (auto& e : r.second->elements)
            {
                if (!e.second->parent)
                {
                    std::cout << "Resizing element: " << e.first << " to " << Width << "x" << Height << std::endl;
                    e.second->size.Bind(BoundingRect(Vec2(0, 0), Vec2(Width, Height)));
                    e.second->Update();
                }
            }

            for (auto& e : r.second->elements)
            {
                if (e.second->parent)
                {
                    e.second->Update();
                }
            }
        }
    }


}
