#pragma once

#include "Types.h"
#include "Item.h"
#include "Mob.h"

class MobGenerator
{
   std::mt19937* _random;
public:
   MobGenerator(std::mt19937* random);

   static std::map<std::string, eTile> NAME_2_TILE;

   Mob GenerateMob(uint32_t level, MobClassLeveling leveling, bool placeItems = false, bool placeInventory = false, uint8_t elite = 1);
};