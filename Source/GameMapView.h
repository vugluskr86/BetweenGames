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

         void SpawnPlayer();
         void SpawnActor();
        
         std::unique_ptr<GameMapViewImpl> self;
      };
   }
}
 