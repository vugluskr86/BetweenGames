#pragma once

#include <memory>
#include <map>

#include "eTiles.h"
#include "Mob.h"

namespace BWG {
   namespace Game {

      struct MobGeneratorImpl;

      class MobGenerator
      {
         std::unique_ptr<MobGeneratorImpl> self;
      public:
       
         static std::map<std::string, eTile> NAME_2_TILE;
         
         MobGenerator();
         ~MobGenerator();

         void Seed(int seed);
         std::unique_ptr<Mob> GenerateMob(uint32_t level, const MobClassLeveling& leveling, bool placeItems = false, bool placeInventory = false, uint8_t elite = 1);
      };
   }
}

