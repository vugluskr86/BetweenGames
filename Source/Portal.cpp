#include "Portal.h"

#include "Player.h"
#include "GameState.h"

namespace BWG {
   namespace Game {

      Portal::Portal(bool isEnd) :
         AbstractGameObject(GOT_PORTAL),
         _isEnd(isEnd)
      {
         //_tile = _isEnd ? eTile::TT_TILES_OBJECTS_PORTAL_END : eTile::TT_TILES_OBJECTS_PORTAL_1;
      }

      void Portal::Teleport(Player& player, GameState& state)
      {
         state.Teleport(player);
      }

   }
}

