#pragma once

#include "Types.h"
#include "Mob.h"

class BattleManager
{
   std::mt19937* _random;
public:
   BattleManager(std::mt19937* random);

   void Battle(Mob& attacker, Mob& defender);

   bool IsChance100(double chance);
};