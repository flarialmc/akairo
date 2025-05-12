#pragma once

class Renderer {

  enum Backends {
      DIRECTX11,
      OPENGL
   };

   enum Frameworks
   {
       ImGUI,
       D2D
   };

  public:
    Backends Backend = OPENGL;
    Frameworks Framework = ImGUI;


};
