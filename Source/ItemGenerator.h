#pragma once

#include <memory>

namespace BWG {
   namespace Game {
   
      class Item;
      struct ItemGeneratorImpl;

      class ItemGenerator
      {
      protected:
         std::unique_ptr<ItemGeneratorImpl> self;
      public:
         ItemGenerator();
         ~ItemGenerator();

         void Seed(int seed);

         std::unique_ptr<Item> GenerateMobItem(eSlotType slot, uint32_t level, std::vector<eItemType> avaliableTypes);
         std::unique_ptr<Item> GenerateTreasueItemByPlayer(uint32_t level);
         std::unique_ptr<Item> GenerateSlotType(eSlotType slot, uint32_t level, std::vector<eItemType> avaliableTypes = {});
      };

   }
}