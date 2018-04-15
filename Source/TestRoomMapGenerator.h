#pragma once

// TestRoomMapGenerator

#include "MapGenerator.h"

namespace BWG {
   namespace Game {
      class TestRoomMapGenerator : public MapGenerator
      {
      public:
         void OnMapGenerate(std::shared_ptr<TileMapType> map) override;
      };
   }
}