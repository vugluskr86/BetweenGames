#pragma once

#include "Types.h"
#include "Mob.h"

class BattleManager
{
   uint32_t _seed;
   std::mt19937 random;

public:
   BattleManager(uint32_t seed);

   void Battle(Mob& attacker, Mob& defender);

   bool IsChance100(double chance);
};