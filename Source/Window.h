#pragma once

#include <memory>
#include "nocopy.h"

struct SDL_Window;
union SDL_Event;

namespace BWG {
   
   namespace Render {
      struct IRenderLayer;
   }
   
   namespace System {
      struct WindowImpl;
      class Window : Utils::nocopy {
      public:
         Window(int width, int height);
         ~Window();
         void Render();
         void HandleResize();
         void AddLayer(std::unique_ptr<Render::IRenderLayer> layer);
         void ProcessEvent(SDL_Event* event);

         static int FRAME;
         bool visible;
         int width, height;
      private:
         std::unique_ptr<WindowImpl> self;
      };
   }
}