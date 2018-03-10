#pragma once

#include "Types.h"
#include "Mob.h"

class Player : public TileObject
{
   Mob _mob;
public:
   Player(eTile tile);
};