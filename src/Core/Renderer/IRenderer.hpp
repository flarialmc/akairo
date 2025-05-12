#pragma once

class IRenderer {
public:
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

public:
    BackendType Backend = OpenGL;
    FrameworkType Framework = ImGUI;

    IRenderer(BackendType backend, FrameworkType framework);

    bool Initialize();

private:
    //ImGui Initializations
    bool InitializeImGUI();
    bool InitializeImGUIOpenGL();
    bool InitializeImGUIDx11();

};
