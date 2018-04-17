#pragma once

#include "nocopy.h"
#include "Array2D.h"

#include <glm/vec2.hpp>

#include <memory>
#include <vector>

#include "Tile.h"
#include "Actor.h"
#include "Action.h"


namespace BWG {

   namespace Utils {
      struct Rect;
   }

   namespace Game {
      
      struct GameMapImpl;

      class GameMap 
      {
         std::unique_ptr<GameMapImpl> self;
      public:
         GameMap();
         ~GameMap();

         const BWG::Utils::Rect & GetWorldBounds() const;

         void AddActor(std::unique_ptr<Actor> actor, int x, int y);

         void Tick();
      };

   }
}