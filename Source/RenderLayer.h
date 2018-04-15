#pragma once

#include <vector>
// #include "nocopy.h"

struct SDL_Window;
union SDL_Event;

namespace BWG {
   namespace Render {
      struct IRenderLayer : Utils::nocopy, std::enable_shared_from_this<IRenderLayer> {
      protected:
         bool _enable;
      public:

         IRenderLayer() : _enable(false) {}
         virtual ~IRenderLayer();

         virtual void Render(SDL_Window* window, bool reset) {}
         virtual void ProcessEvent(SDL_Event* event) {}

         void Enable() { _enable = true; }
         void Disable() { _enable = false; }
         bool IsEnabled() const { return _enable; }

         std::shared_ptr<IRenderLayer> getptr() {
            return shared_from_this();
         }
      };
   }
}

