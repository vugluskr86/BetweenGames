#pragma once

#include "Types.h"
#include "Mob.h"

class BattleManager;

class Monster : public TileObject
{
   Mob _mob;
   std::string _name;
public:
   Mob & GetMobPtr()
   { return _mob; }
   std::string GetName() { return _name; }

   void OnPlayerAttack(BattleManager* manager, Player* player);

   Monster(eTile tile, const std::string& baseName, Mob mob);
};