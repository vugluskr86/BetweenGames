#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Direction.h"

namespace BWG {
   namespace Game {

      class Action;

      struct PlayerImpl;

      class Player
      {
         std::unique_ptr<PlayerImpl> self;
      public:
         Player();
         ~Player();
      };

   }
}