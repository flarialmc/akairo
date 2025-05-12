#pragma once

class Renderer {
public:
    enum Backends {
      UndefinedBackend,
      DIRECTX11,
      OPENGL
   };

    enum Frameworks
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
    Backends Backend = OPENGL;
    Frameworks Framework = ImGUI;

    Renderer(Backends backend, Frameworks framework);

    bool Initialize();

private:
    //ImGui Initializations
    bool InitializeImGUI();
    bool InitializeImGUIOpenGL();
    bool InitializeImGUIDx11();

};
