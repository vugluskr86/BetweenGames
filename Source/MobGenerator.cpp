#include "MobGenerator.h"
#include "ItemGenerator.h"

MobGenerator::MobGenerator(uint32_t seed) :
   _seed(seed)
{
   random.seed(seed);
}

Mob MobGenerator::GenerateMob(uint32_t level, MobClassLeveling leveling, bool placeItems, bool placeInventory, uint8_t elite)
{
   ItemGenerator itemGen(_seed);

   Mob mob;
   mob._level = level;
   mob._class = leveling;
   mob._elite = elite;

   if(placeItems) {
      // TODO : Generate items all slot
      mob.AddSlotItem(ST_LEFT_HAND, itemGen.GenerateMobItem(ST_LEFT_HAND, level));
   }

   if(placeInventory) {
      // TODO : Create inventory
   }
      
   mob.CalcParams(mob._level);
   
   return mob;
}