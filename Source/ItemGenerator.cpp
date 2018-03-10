#include "ItemGenerator.h"

const std::vector<ItemProtValue> ItemGenerator::Prototypes = {
	//2h
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_ATTACKPWMULTMAX,1,1.5 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_ELEMDAMAGE_PYRE,1,15 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_ELEMDAMAGE_FIRE,1,15 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_ELEMDAMAGE_COLD,1,15 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_ELEMDAMAGE_LIGHTNING,1,15 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_ELEMDAMAGE_ACID,1,15 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_ELEMDAMAGE_LIGHT,1,15 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_ELEMDAMAGE_DARKNESS,1,15 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_ATTACKPWR,1,40 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_HP,1,20 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_CRIT,1,3 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_ABSORB,1,1 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_STUNCHANCE,1,10 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_ATTACKPWMULTMAX,2,1.7 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_ELEMDAMAGE_PYRE,2,25 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_ELEMDAMAGE_FIRE,2,25 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_ELEMDAMAGE_COLD,2,25 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_ELEMDAMAGE_LIGHTNING,2,25 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_ELEMDAMAGE_ACID,2,25 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_ELEMDAMAGE_LIGHT,2,25 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_ELEMDAMAGE_DARKNESS,2,25 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_ATTACKPWR,2,80 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_HP,2,40 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_CRIT,2,5 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_ABSORB,2,2 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_STUNCHANCE,2,15 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_ATTACKPWMULTMAX,3,1.9 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_ELEMDAMAGE_PYRE,3,35 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_ELEMDAMAGE_FIRE,3,35 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_ELEMDAMAGE_COLD,3,35 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_ELEMDAMAGE_LIGHTNING,3,35 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_ELEMDAMAGE_ACID,3,35 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_ELEMDAMAGE_LIGHT,3,35 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_ELEMDAMAGE_DARKNESS,3,35 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_ATTACKPWR,3,160 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_HP,3,80 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_CRIT,3,7 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_ABSORB,3,3 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_STUNCHANCE,3,20 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_ATTACKPWMULTMAX,4,2.1 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_ELEMDAMAGE_PYRE,4,45 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_ELEMDAMAGE_FIRE,4,45 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_ELEMDAMAGE_COLD,4,45 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_ELEMDAMAGE_LIGHTNING,4,45 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_ELEMDAMAGE_ACID,4,45 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_ELEMDAMAGE_LIGHT,4,45 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_ELEMDAMAGE_DARKNESS,4,45 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_ATTACKPWR,4,320 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_HP,4,160 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_CRIT,4,9 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_ABSORB,4,4 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_STUNCHANCE,4,25 },
	//1h
	{ WT_WEAPON_1H,ST_RIGHT_HAND,IP_ATTACKPWMULTMAX,1,1.2 },
	{ WT_WEAPON_1H,ST_RIGHT_HAND,IP_ELEMDAMAGE_PYRE,1,20 },
	{ WT_WEAPON_1H,ST_RIGHT_HAND,IP_ELEMDAMAGE_FIRE,1,20 },
	{ WT_WEAPON_1H,ST_RIGHT_HAND,IP_ELEMDAMAGE_COLD,1,20 },
	{ WT_WEAPON_1H,ST_RIGHT_HAND,IP_ELEMDAMAGE_LIGHTNING,1,20 },
	{ WT_WEAPON_1H,ST_RIGHT_HAND,IP_ELEMDAMAGE_ACID,1,20 },
	{ WT_WEAPON_1H,ST_RIGHT_HAND,IP_ELEMDAMAGE_LIGHT,1,20 },
	{ WT_WEAPON_1H,ST_RIGHT_HAND,IP_ELEMDAMAGE_DARKNESS,1,20 },
	{ WT_WEAPON_1H,ST_RIGHT_HAND,IP_ATTACKPWR,1,10 },
	{ WT_WEAPON_1H,ST_RIGHT_HAND,IP_ATTACKPERTURN,1,2 },
	{ WT_WEAPON_1H,ST_RIGHT_HAND,IP_CRIT,1,3 },
	{ WT_WEAPON_1H,ST_RIGHT_HAND,IP_ABSORB,1,1 },
	{ WT_WEAPON_1H,ST_RIGHT_HAND,IP_BLEEDCHANCE,1,10 },
	{ WT_WEAPON_1H,ST_RIGHT_HAND,IP_ATTACKPWMULTMAX,2,1.4 },
	{ WT_WEAPON_1H,ST_RIGHT_HAND,IP_ELEMDAMAGE_PYRE,2,30 },
	{ WT_WEAPON_1H,ST_RIGHT_HAND,IP_ELEMDAMAGE_FIRE,2,30 },
	{ WT_WEAPON_1H,ST_RIGHT_HAND,IP_ELEMDAMAGE_COLD,2,30 },
	{ WT_WEAPON_1H,ST_RIGHT_HAND,IP_ELEMDAMAGE_LIGHTNING,2,30 },
	{ WT_WEAPON_1H,ST_RIGHT_HAND,IP_ELEMDAMAGE_ACID,2,30 },
	{ WT_WEAPON_1H,ST_RIGHT_HAND,IP_ELEMDAMAGE_LIGHT,2,30 },
	{ WT_WEAPON_1H,ST_RIGHT_HAND,IP_ELEMDAMAGE_DARKNESS,2,30 },
	{ WT_WEAPON_1H,ST_RIGHT_HAND,IP_ATTACKPWR,2,20 },
	{ WT_WEAPON_1H,ST_RIGHT_HAND,IP_ATTACKPERTURN,2,3 },
	{ WT_WEAPON_1H,ST_RIGHT_HAND,IP_CRIT,2,5 },
	{ WT_WEAPON_1H,ST_RIGHT_HAND,IP_ABSORB,2,2 },
	{ WT_WEAPON_1H,ST_RIGHT_HAND,IP_BLEEDCHANCE,2,15 },
	{ WT_WEAPON_1H,ST_RIGHT_HAND,IP_ATTACKPWMULTMAX,3,1.6 },
	{ WT_WEAPON_1H,ST_RIGHT_HAND,IP_ELEMDAMAGE_PYRE,3,40 },
	{ WT_WEAPON_1H,ST_RIGHT_HAND,IP_ELEMDAMAGE_FIRE,3,40 },
	{ WT_WEAPON_1H,ST_RIGHT_HAND,IP_ELEMDAMAGE_COLD,3,40 },
	{ WT_WEAPON_1H,ST_RIGHT_HAND,IP_ELEMDAMAGE_LIGHTNING,3,40 },
	{ WT_WEAPON_1H,ST_RIGHT_HAND,IP_ELEMDAMAGE_ACID,3,40 },
	{ WT_WEAPON_1H,ST_RIGHT_HAND,IP_ELEMDAMAGE_LIGHT,3,40 },
	{ WT_WEAPON_1H,ST_RIGHT_HAND,IP_ELEMDAMAGE_DARKNESS,3,40 },
	{ WT_WEAPON_1H,ST_RIGHT_HAND,IP_ATTACKPWR,3,30 },
	{ WT_WEAPON_1H,ST_RIGHT_HAND,IP_ATTACKPERTURN,3,4 },
	{ WT_WEAPON_1H,ST_RIGHT_HAND,IP_CRIT,3,7 },
	{ WT_WEAPON_1H,ST_RIGHT_HAND,IP_ABSORB,3,3 },
	{ WT_WEAPON_1H,ST_RIGHT_HAND,IP_BLEEDCHANCE,3,20 },
	{ WT_WEAPON_1H,ST_RIGHT_HAND,IP_ATTACKPWMULTMAX,4,1.8 },
	{ WT_WEAPON_1H,ST_RIGHT_HAND,IP_ELEMDAMAGE_PYRE,4,50 },
	{ WT_WEAPON_1H,ST_RIGHT_HAND,IP_ELEMDAMAGE_FIRE,4,50 },
	{ WT_WEAPON_1H,ST_RIGHT_HAND,IP_ELEMDAMAGE_COLD,4,50 },
	{ WT_WEAPON_1H,ST_RIGHT_HAND,IP_ELEMDAMAGE_LIGHTNING,4,50 },
	{ WT_WEAPON_1H,ST_RIGHT_HAND,IP_ELEMDAMAGE_ACID,4,50 },
	{ WT_WEAPON_1H,ST_RIGHT_HAND,IP_ELEMDAMAGE_LIGHT,4,50 },
	{ WT_WEAPON_1H,ST_RIGHT_HAND,IP_ELEMDAMAGE_DARKNESS,4,50 },
	{ WT_WEAPON_1H,ST_RIGHT_HAND,IP_ATTACKPWR,4,40 },
	{ WT_WEAPON_1H,ST_RIGHT_HAND,IP_ATTACKPERTURN,4,5 },
	{ WT_WEAPON_1H,ST_RIGHT_HAND,IP_CRIT,4,9 },
	{ WT_WEAPON_1H,ST_RIGHT_HAND,IP_ABSORB,4,4 },
	{ WT_WEAPON_1H,ST_RIGHT_HAND,IP_BLEEDCHANCE,4,25 },
	//shield
	{ WT_SHIELD,ST_LEFT_HAND,IP_BLOCKVAL,1,25 },
	{ WT_SHIELD,ST_LEFT_HAND,IP_PHYSRES,1,20 },
	{ WT_SHIELD,ST_LEFT_HAND,IP_FIRERES,1,10 },
	{ WT_SHIELD,ST_LEFT_HAND,IP_COLDRES,1,10 },
	{ WT_SHIELD,ST_LEFT_HAND,IP_LIGHTRES,1,10 },
	{ WT_SHIELD,ST_LEFT_HAND,IP_ACIDRES,1,10 },
	{ WT_SHIELD,ST_LEFT_HAND,IP_BLOCKCHANCE,1,40 },
	{ WT_SHIELD,ST_LEFT_HAND,IP_BLOCKVAL,2,50 },
	{ WT_SHIELD,ST_LEFT_HAND,IP_PHYSRES,2,30 },
	{ WT_SHIELD,ST_LEFT_HAND,IP_FIRERES,2,20 },
	{ WT_SHIELD,ST_LEFT_HAND,IP_COLDRES,2,20 },
	{ WT_SHIELD,ST_LEFT_HAND,IP_LIGHTRES,2,20 },
	{ WT_SHIELD,ST_LEFT_HAND,IP_ACIDRES,2,20 },
	{ WT_SHIELD,ST_LEFT_HAND,IP_BLOCKCHANCE,2,50 },
	{ WT_SHIELD,ST_LEFT_HAND,IP_BLOCKVAL,3,100 },
	{ WT_SHIELD,ST_LEFT_HAND,IP_PHYSRES,3,40 },
	{ WT_SHIELD,ST_LEFT_HAND,IP_FIRERES,3,30 },
	{ WT_SHIELD,ST_LEFT_HAND,IP_COLDRES,3,30 },
	{ WT_SHIELD,ST_LEFT_HAND,IP_LIGHTRES,3,30 },
	{ WT_SHIELD,ST_LEFT_HAND,IP_ACIDRES,3,30 },
	{ WT_SHIELD,ST_LEFT_HAND,IP_BLOCKCHANCE,3,60 },
	{ WT_SHIELD,ST_LEFT_HAND,IP_BLOCKVAL,4,200 },
	{ WT_SHIELD,ST_LEFT_HAND,IP_PHYSRES,4,50 },
	{ WT_SHIELD,ST_LEFT_HAND,IP_FIRERES,4,40 },
	{ WT_SHIELD,ST_LEFT_HAND,IP_COLDRES,4,40 },
	{ WT_SHIELD,ST_LEFT_HAND,IP_LIGHTRES,4,40 },
	{ WT_SHIELD,ST_LEFT_HAND,IP_ACIDRES,4,40 },
	{ WT_SHIELD,ST_LEFT_HAND,IP_BLOCKCHANCE,4,70 }
};

static double GetPrototypeProperyValue(const std::vector<ItemProtValue>& list, eBalancePropery prop, uint32_t tier)
{
   auto it = std::find_if(list.begin(), list.end(), [prop, tier](auto check) {
      return check.prop == prop && check.tier == tier;
   });

   assert(it != list.end());

   return it->value;
}

template<typename ST>
ST GetSample(const std::unordered_set<ST>& s, int index) {
   double r = index % s.size();
   auto it = s.begin();
   for(; r != 0; r--) it++;
   return *it;
}

ItemGenerator::ItemGenerator(uint32_t seed) :
   _seed(seed)
{
   random.seed(seed);
}

Item ItemGenerator::GenerateSlotType(eSlotType slot, uint32_t level)
{
   Item item;

   item.slot = slot;

   // Generate tier at level
   const std::vector<uint32_t> tier_level_range = { 0, 5, 10, 15 };
   auto tier_range = std::equal_range(tier_level_range.begin(), tier_level_range.end(), level);
   auto left = tier_range.first - tier_level_range.begin();
   auto right = tier_range.second - tier_level_range.begin();

   item.tier = std::uniform_int_distribution<int>(left, right)(random);

   assert(item.tier != 0);

   // Generate item type
   std::unordered_set<eItemType> types;
   std::vector<ItemProtValue> slotPrototypes;
   for(auto prot : ItemGenerator::Prototypes) {
      if(prot.slot == slot && prot.tier == item.tier) {
         slotPrototypes.push_back(prot);
         types.insert(prot.type);
      }
   }

   auto _type = std::uniform_int_distribution<int>(0, types.size() - 1)(random);

   item.type = GetSample(types, _type);

   // Generate random color TODO: weight
   int color_interval[] = { 0, 1, 2, 3, 4, 5, 6 };
   double color_weights[] = { 7, 6, 5, 4, 3, 2, 1 };
   std::piecewise_constant_distribution<> dist_color(std::begin(color_interval),
      std::end(color_interval),
      std::begin(color_weights));

   auto prefix_count = (int)dist_color(random);

   item.color = prefix_count;

   if(item.IsWeapon()) {
      item.params[eBalancePropery::IP_ATTACKPWMULTMAX] = std::uniform_real_distribution<>(1, GetPrototypeProperyValue(slotPrototypes, eBalancePropery::IP_ATTACKPWMULTMAX, item.tier))(random);
   }

   if(item.IsShield()) {
      item.params[eBalancePropery::IP_BLOCKVAL] = std::uniform_real_distribution<>(1, GetPrototypeProperyValue(slotPrototypes, eBalancePropery::IP_BLOCKVAL, item.tier))(random);
   }

   std::vector<eBalancePropery> addProperties;

   if(prefix_count > 0) {
      switch(item.type) {
      /*case WT_WEAPON_RIFLE: {
         addProperties = { IP_ELEMDAMAGE, IP_ATTACKPWR, IP_RANGE, IP_CRIT, IP_DODGE };
         if(prefix_count > 6) addProperties.push_back(IP_DAZECHANCE);
         break;
      }*/
      case WT_WEAPON_2H: {
		  addProperties = { IP_ELEMDAMAGE_PYRE,
			  IP_ELEMDAMAGE_FIRE,
			  IP_ELEMDAMAGE_COLD,
			  IP_ELEMDAMAGE_LIGHTNING,
			  IP_ELEMDAMAGE_ACID,
			  IP_ELEMDAMAGE_LIGHT,
			  IP_ELEMDAMAGE_DARKNESS, IP_ATTACKPWR, IP_HP, IP_CRIT, IP_ABSORB };
         if(prefix_count == 6) addProperties.push_back(IP_STUNCHANCE);
         break;
      }
      case WT_WEAPON_1H: {
		  addProperties = { IP_ELEMDAMAGE_PYRE,
			  IP_ELEMDAMAGE_FIRE,
			  IP_ELEMDAMAGE_COLD,
			  IP_ELEMDAMAGE_LIGHTNING,
			  IP_ELEMDAMAGE_ACID,
			  IP_ELEMDAMAGE_LIGHT,
			  IP_ELEMDAMAGE_DARKNESS, IP_ATTACKPWR, IP_ATTACKPERTURN, IP_CRIT, IP_ABSORB };
         if(prefix_count == 6) addProperties.push_back(IP_BLEEDCHANCE);
         break;
      }
      case WT_SHIELD: {
         addProperties = { 
            IP_BLOCKVAL,
            IP_PHYSRES,
            IP_FIRERES,
            IP_COLDRES,
            IP_LIGHTRES,
            IP_ACIDRES
         };
         if(prefix_count == 6) addProperties.push_back(IP_BLOCKCHANCE);
         break;
      }
      }
   }

   for(int i = 0; i < prefix_count; i++) {
      eBalancePropery add_property = *select_randomly(addProperties.begin(), addProperties.end(), random);
      auto val = std::uniform_real_distribution<>(1, GetPrototypeProperyValue(slotPrototypes, add_property, item.tier))(random);
      auto exists = item.params.find(add_property);
      if(exists == item.params.end()) {
         item.params[add_property] = val;
      }
      else {
         item.params[add_property] += val;
      }
   }

   return item;
}

Item ItemGenerator::GenerateMobItem(eSlotType slot, uint32_t level)
{
   return GenerateSlotType(slot, level);
}

Item ItemGenerator::GenerateTreasueItemByPlayer(uint32_t level)
{
   // Generate random damage type
   int interval[] = { eSlotType::ST_RIGHT_HAND };
   double weights[] = { 1 };
   std::piecewise_constant_distribution<> dist(std::begin(interval),
      std::end(interval),
      std::begin(weights));

   return GenerateSlotType((eSlotType)(int)dist(random), level);
}

