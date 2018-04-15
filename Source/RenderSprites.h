#pragma once

#include <memory>
#include "nocopy.h"
#include "RenderLayer.h"

struct SDL_Window;

namespace BWG {
   namespace Render {

      struct RenderTilesImpl;

      struct Sprite {
         int image_id;
         double x, y;
      };

      class RenderSprites : public IRenderLayer {
      public:
         RenderSprites();
         ~RenderSprites();
         virtual void Render(SDL_Window* window, bool reset);

         void SetTiles(const std::vector<Sprite>& sprites);

      protected:
         std::unique_ptr<RenderTilesImpl> self;
      };

   }
}

