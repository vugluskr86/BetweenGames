#pragma once

#include <memory>

#include "Direction.h"

namespace BWG {
   namespace Game {

      class GameMapView;
      class PlayerAction;

      struct PlayerImpl;

      class Player
      {
         std::unique_ptr<PlayerImpl> self;
      public:
         Player();
         ~Player();

         void Action(std::shared_ptr<PlayerAction> action, std::shared_ptr<GameMapView> map);
      };

   }
}