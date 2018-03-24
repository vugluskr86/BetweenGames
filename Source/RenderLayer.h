#pragma once

#include <vector>
#include "nocopy.h"

struct SDL_Window;
union SDL_Event;

namespace BWG {
   namespace Render {

      struct IRenderLayer : Utils::nocopy {
         virtual void Render(SDL_Window* window, bool reset) {}
         virtual void ProcessEvent(SDL_Event* event) {}
         virtual ~IRenderLayer();
      };

   }
}

