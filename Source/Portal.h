#pragma once

#include "GameCommon.h"
#include "TileMap.h"

namespace BWG {
   namespace Game {

      class GameState;
      class Player;

      class Portal : public AbstractGameObject
      {
         bool _isEnd;
      public:
         Portal(bool isEnd);

         void Teleport(Player& player, GameState& state);

         bool IsEnd() const { return _isEnd; }
      };
   }
}
