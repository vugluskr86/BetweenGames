#pragma once

#include "nocopy.h"
#include "RenderLayer.h"
#include "eTiles.h"

struct SDL_Window;

namespace BWG {
   namespace Render {

      struct RenderTilesImpl;

      struct Tile {
         int image_id;
         double x, y;
      };

      class RenderTiles : public IRenderLayer {
      public:
         RenderTiles();
         ~RenderTiles();
         virtual void Render(SDL_Window* window, bool reset);

         void SetTiles(const std::vector<Tile>& sprites);

      protected:
         std::unique_ptr<RenderTilesImpl> self;
      };

   }
}

