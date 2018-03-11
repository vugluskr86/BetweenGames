#pragma once

#include "Types.h"
#include "Mob.h"

class Player : public TileObject
{
   Mob _mob;
   std::string _name;
   uint32_t _exp;
public:
   Player(eTile tile, const std::string& baseName, Mob mob, double appendHp = 1.0);

   uint32_t GetExp() const 
   { return _exp; }

   void AddExp(uint32_t exp);
   void Reset() {
      _exp = 0;
   }

   Mob& GetMobPtr()
   { return _mob; }
   std::string GetName() { return _name; }
};