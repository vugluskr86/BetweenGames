#pragma once

#include "Types.h"
#include "Mob.h"

class Player : public TileObject
{
   Mob _mob;
   std::string _name;
public:
   Player(eTile tile, const std::string& baseName, Mob mob, double appendHp = 1.0);

   Mob& GetMobPtr()
   { return _mob; }
   std::string GetName() { return _name; }
};