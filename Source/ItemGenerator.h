#pragma once

#include <memory>

namespace BWG {
   namespace Game {
   
      class Item;
      struct ItemGeneratorImpl;

      class ItemGenerator
      {
         std::unique_ptr<ItemGeneratorImpl> self;
      public:
         ItemGenerator();

         void Seed(int seed);

         Item* GenerateMobItem(eSlotType slot, uint32_t level, std::vector<eItemType> avaliableTypes);
         Item* GenerateTreasueItemByPlayer(uint32_t level);
         Item* GenerateSlotType(eSlotType slot, uint32_t level, std::vector<eItemType> avaliableTypes = {});
      };

   }
}