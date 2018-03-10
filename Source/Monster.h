#pragma once

#include "Types.h"
#include "Mob.h"

class Monster : public TileObject
{
   Mob _mob;
public:
   Monster(eTile tile);
};