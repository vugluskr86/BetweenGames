#pragma once

#include "Types.h"
#include "Item.h"

struct ItemProtValue
{
   eItemType type;
   eSlotType slot;
   eBalancePropery prop;
   uint32_t tier;
   float value;
};

class ItemGenerator
{
   uint32_t _seed;
   std::mt19937 random;
   
   static const std::vector<ItemProtValue> Prototypes;
public:
   ItemGenerator(uint32_t seed);

   Item GenerateMobItem(eSlotType slot, uint32_t level);
   Item GenerateTreasueItemByPlayer(uint32_t level);
   Item GenerateSlotType(eSlotType slot, uint32_t level);
};