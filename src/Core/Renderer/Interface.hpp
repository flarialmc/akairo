#pragma once

namespace akairo::Renderer {

    enum BackendType {

        UndefinedBackend,
        DirectX11,
        OpenGL

     };

    enum FrameworkType
    {
        UndefinedFramework,
        ImGUI,
        D2D
    };

    enum OSType
    {
        Andorid,
        Windows
    };

    class Interface {
    public:
        BackendType backend = OpenGL;

        Interface(BackendType backend) {
            this->backend = backend;
          }

        bool Initialize();
    };
}
