#pragma once

#include "PlayerAction.h"

namespace BWG {
   namespace Game {

      class PlayerActionMove : public PlayerAction
      {
      public:
         ePlayerActions GetType() const override { return EPA_ATTACK; }

         void Proceed(std::shared_ptr<GameMapView> map, std::shared_ptr<Player> Player) override;
      };
   }
}