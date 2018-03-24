#pragma once

#include <memory>
#include "nocopy.h"
#include "RenderLayer.h"

struct SDL_Window;

namespace BWG {
   namespace Render {

      struct RenderImGuiImpl;

      class RenderImGui : public IRenderLayer {
      public:
         RenderImGui();
         ~RenderImGui();
         virtual void Render(SDL_Window* window, bool reset);
         virtual void ProcessEvent(SDL_Event* event);

      protected:
         std::unique_ptr<RenderImGuiImpl> self;
      };

   }
}

