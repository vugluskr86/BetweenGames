#include "MobGenerator.h"
#include "ItemGenerator.h"

std::map<std::string, eTile> MobGenerator::NAME_2_TILE = {
   { "Dragon Warrior", TT_TILES_MONSTERS_DRAGON_WARRIOR_3},
   { "Fairy", TT_TILES_MONSTERS_FAIRY_3 },
   { "Invoker", TT_TILES_MONSTERS_INVOKER_1 },
   { "Human", TT_TILES_MONSTERS_HUMAN_1 },
   { "Ogre", TT_TILES_MONSTERS_OGRE }
};

MobGenerator::MobGenerator(std::mt19937* random)
{
   _random = random;
}

Mob MobGenerator::GenerateMob(uint32_t level, MobClassLeveling leveling, bool placeItems, bool placeInventory, uint8_t elite)
{
   ItemGenerator itemGen(_random);

   Mob mob;
   mob._level = level;
   mob._class = leveling;
   mob._elite = elite;

   std::uniform_real_distribution<> rnd01(0, 1);

   if(placeItems) {
      // TODO : Generate items all slot
     
      bool _shieldGen = false;
      auto chanceShield = rnd01(*_random);
      if(chanceShield > 0.5) {
         mob.AddSlotItem(ST_LEFT_HAND, itemGen.GenerateMobItem(ST_LEFT_HAND, level, { eItemType::WT_SHIELD }));
         _shieldGen = true;
      }

      if(_shieldGen) {
         mob.AddSlotItem(ST_RIGHT_HAND, itemGen.GenerateMobItem(ST_RIGHT_HAND, level, { eItemType::WT_WEAPON_1H }));
      } else {
         auto chance2h = rnd01(*_random);
         if(chance2h > 0.5) {
            mob.AddSlotItem(ST_RIGHT_HAND, itemGen.GenerateMobItem(ST_RIGHT_HAND, level, { eItemType::WT_WEAPON_2H }));
         } else {
            auto chance1hIn2 = rnd01(*_random);
            if(chance1hIn2 > 0.5) {
               mob.AddSlotItem(ST_RIGHT_HAND, itemGen.GenerateMobItem(ST_RIGHT_HAND, level, { eItemType::WT_WEAPON_1H }));
               mob.AddSlotItem(ST_LEFT_HAND, itemGen.GenerateMobItem(ST_LEFT_HAND, level, { eItemType::WT_WEAPON_1H }));
            } else {
               mob.AddSlotItem(ST_RIGHT_HAND, itemGen.GenerateMobItem(ST_RIGHT_HAND, level, { eItemType::WT_WEAPON_1H }));
            }
         }
      }

      
   }

   if(placeInventory) {
      // TODO : Create inventory
   }
      
   mob.CalcParams(mob._level);
   
   return mob;
}