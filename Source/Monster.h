#pragma once

#include "Types.h"
#include "Mob.h"

class Monster : public TileObject
{
   Mob _mob;
   std::string _name;
public:
   Mob & GetMobPtr()
   { return _mob; }
   std::string GetName() { return _name; }

   Monster(eTile tile, const std::string& baseName, Mob mob);
};