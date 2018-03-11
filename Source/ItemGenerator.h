#pragma once

#include "Types.h"
#include "Item.h"

struct ItemProtValue
{
   eItemType type;
   eSlotType slot;
   eBalancePropery prop;
   uint32_t tier;
   double value;
};

class ItemGenerator
{
   std::mt19937* _random;
   
   static const std::vector<ItemProtValue> Prototypes;
public:
   ItemGenerator(std::mt19937* random);

   Item GenerateMobItem(eSlotType slot, uint32_t level);
   Item GenerateTreasueItemByPlayer(uint32_t level);
   Item GenerateSlotType(eSlotType slot, uint32_t level);
};