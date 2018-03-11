#pragma once

#include "Types.h"

class GameState;

class Portal : public TileObject
{
   GameState* _state;
   bool _isEnd;
public:
   Portal(GameState* state, bool isEnd);
   void Teleport(Player* player);
};