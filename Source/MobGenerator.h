#pragma once

#include "Types.h"
#include "Item.h"
#include "Mob.h"

class MobGenerator
{
   uint32_t _seed;
   std::mt19937 random;
public:
   MobGenerator(uint32_t seed);

   Mob GenerateMob(uint32_t level, MobClassLeveling leveling, bool placeItems = false, bool placeInventory = false, uint8_t elite = 0);
};