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


    public:
        BackendType backend = OpenGL;

        Interface(BackendType backend) {
            this->backend = backend;
          }

        bool Initialize();

    private:
        //ImGui Initializations
        bool InitializeImGUI();
        bool InitializeImGUIOpenGL();
        bool InitializeImGUIDx11();

    };
}
