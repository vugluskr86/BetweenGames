#include "Portal.h"

#include "Player.h"
#include "GameState.h"

Portal::Portal(GameState* state, bool isEnd) :
   _state(state)
{
   _type = TO_PORTAL;
   _isEnd = isEnd;
   _tile = _isEnd ? eTile::TT_TILES_OBJECTS_PORTAL_END : eTile::TT_TILES_OBJECTS_PORTAL_1;
}

void Portal::Teleport(Player* player)
{
   _state->Teleport(player);
}