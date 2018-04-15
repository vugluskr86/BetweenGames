#pragma once

// MapGenerator
#include <memory>
#include "TileMap.h"

namespace BWG {
   namespace Game {
      class MapGenerator
      {
      public:
         virtual void OnMapGenerate(std::shared_ptr<TileMapType> map) = 0;
      };
   }
}