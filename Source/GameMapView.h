#pragma once

#include <memory>

namespace BWG {
   namespace Game {

      struct GameMapViewImpl;

      class GameMapView
      {
      public:
         GameMapView();
         ~GameMapView();

         std::unique_ptr<GameMapViewImpl> self;
      };
   }
}
 