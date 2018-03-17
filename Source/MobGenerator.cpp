#include "Common.h"
#include "GameCommon.h"
#include "GameObject.h"
#include "MobGenerator.h"
#include "ItemGenerator.h"
#include "i18n.h"
#include "Item.h"
#include "RandomUtils.h"
#include "eTiles.h"
#include "Mob.h"

#include <random>

namespace BWG {
   namespace Game {

      std::map<std::string, eTile> MobGenerator::NAME_2_TILE = {
         { "Dragon Warrior", TT_TILES_MONSTERS_DRAGON_WARRIOR_3 },
         { "Fairy", TT_TILES_MONSTERS_FAIRY_3 },
         { "Invoker", TT_TILES_MONSTERS_INVOKER_1 },
         { "Human", TT_TILES_MONSTERS_HUMAN_1 },
         { "Ogre", TT_TILES_MONSTERS_OGRE }
      };

      struct MobGeneratorImpl {
         int _seed;
         std::mt19937 _random;

         MobGeneratorImpl() {}
      };

      MobGenerator::MobGenerator() :
         self(new MobGeneratorImpl())
      {}

      MobGenerator::~MobGenerator() {}

      void MobGenerator::Seed(int seed)
      {
         self->_seed = seed;
         self->_random.seed(seed);
      }

      std::unique_ptr<Mob> MobGenerator::GenerateMob(uint32_t level, const MobClassLeveling& leveling, bool placeItems, bool placeInventory, uint8_t elite)
      {
         ItemGenerator itemGen;

         itemGen.Seed(self->_seed);

         std::unique_ptr<Mob> mob = std::make_unique<Mob>(level, leveling, elite);

         std::uniform_real_distribution<> rnd01(0, 1);

         if(placeItems) {
            bool _shieldGen = false;
            auto chanceShield = rnd01(self->_random);
            if(chanceShield > 0.5) {
               mob->AddSlotItem(ST_LEFT_HAND, itemGen.GenerateMobItem(ST_LEFT_HAND, level, { eItemType::WT_SHIELD }));
               _shieldGen = true;
            }
            if(_shieldGen) {
               mob->AddSlotItem(ST_RIGHT_HAND, itemGen.GenerateMobItem(ST_RIGHT_HAND, level, { eItemType::WT_WEAPON_1H }));
            }
            else {
               auto chance2h = rnd01(self->_random);
               if(chance2h > 0.5) {
                  mob->AddSlotItem(ST_RIGHT_HAND, itemGen.GenerateMobItem(ST_RIGHT_HAND, level, { eItemType::WT_WEAPON_2H }));
               }
               else {
                  auto chance1hIn2 = rnd01(self->_random);
                  if(chance1hIn2 > 0.5) {
                     mob->AddSlotItem(ST_RIGHT_HAND, itemGen.GenerateMobItem(ST_RIGHT_HAND, level, { eItemType::WT_WEAPON_1H }));
                     mob->AddSlotItem(ST_LEFT_HAND, itemGen.GenerateMobItem(ST_LEFT_HAND, level, { eItemType::WT_WEAPON_1H }));
                  }
                  else {
                     mob->AddSlotItem(ST_RIGHT_HAND, itemGen.GenerateMobItem(ST_RIGHT_HAND, level, { eItemType::WT_WEAPON_1H }));
                  }
               }
            }
         }

         if(placeInventory) {
            // TODO : Create inventory
         }


         return std::move(mob);
      }
   }
}