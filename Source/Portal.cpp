#include "Portal.h"

#include "Player.h"
#include "GameState.h"

Portal::Portal(GameState* state) : 
   _state(state)
{
   _type = TO_PORTAL;
   _tile = eTile::TT_TILES_OBJECTS_PORTAL_1;
}

void Portal::Teleport(Player* player)
{
   _state->Teleport(player);
}