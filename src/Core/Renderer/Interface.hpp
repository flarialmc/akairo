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
        BackendType Backend = OpenGL;
        FrameworkType Framework = ImGUI;

        Interface(akairo::Renderer::BackendType backend, akairo::Renderer::FrameworkType framework) {
            this->Backend = backend;
            this->Framework = framework;
          };

        bool Initialize();

    private:
        //ImGui Initializations
        bool InitializeImGUI();
        bool InitializeImGUIOpenGL();
        bool InitializeImGUIDx11();

    };
}
