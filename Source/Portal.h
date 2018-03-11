#pragma once

#include "Types.h"

class GameState;

class Portal : public TileObject
{
   GameState* _state;
public:
   Portal(GameState* state);
   void Teleport(Player* player);
};