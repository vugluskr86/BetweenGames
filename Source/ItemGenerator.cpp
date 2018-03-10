#include "ItemGenerator.h"

const std::vector<ItemProtValue> ItemGenerator::Prototypes = {
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_ATTACKPWMULTMAX,1,15 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_ELEMDAMAGE_PYRE,1,150 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_ELEMDAMAGE_FIRE,1,150 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_ELEMDAMAGE_COLD,1,150 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_ELEMDAMAGE_LIGHTNING,1,150 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_ELEMDAMAGE_ACID,1,150 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_ELEMDAMAGE_LIGHT,1,150 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_ELEMDAMAGE_DARKNESS,1,150 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_ATTACKPWR,1,400 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_HP,1,200 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_CRIT,1,30 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_ABSORB,1,10 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_STUNCHANCE,1,100 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_ATTACKPWMULTMAX,2,17 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_ELEMDAMAGE_PYRE,2,250 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_ELEMDAMAGE_FIRE,2,250 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_ELEMDAMAGE_COLD,2,250 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_ELEMDAMAGE_LIGHTNING,2,250 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_ELEMDAMAGE_ACID,2,250 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_ELEMDAMAGE_LIGHT,2,250 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_ELEMDAMAGE_DARKNESS,2,250 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_ATTACKPWR,2,800 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_HP,2,400 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_CRIT,2,50 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_ABSORB,2,20 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_STUNCHANCE,2,150 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_ATTACKPWMULTMAX,3,19 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_ELEMDAMAGE_PYRE,3,350 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_ELEMDAMAGE_FIRE,3,350 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_ELEMDAMAGE_COLD,3,350 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_ELEMDAMAGE_LIGHTNING,3,350 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_ELEMDAMAGE_ACID,3,350 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_ELEMDAMAGE_LIGHT,3,350 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_ELEMDAMAGE_DARKNESS,3,350 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_ATTACKPWR,3,1600 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_HP,3,800 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_CRIT,3,70 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_ABSORB,3,30 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_STUNCHANCE,3,200 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_ATTACKPWMULTMAX,4,21 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_ELEMDAMAGE_PYRE,4,450 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_ELEMDAMAGE_FIRE,4,450 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_ELEMDAMAGE_COLD,4,450 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_ELEMDAMAGE_LIGHTNING,4,450 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_ELEMDAMAGE_ACID,4,450 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_ELEMDAMAGE_LIGHT,4,450 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_ELEMDAMAGE_DARKNESS,4,450 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_ATTACKPWR,4,3200 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_HP,4,1600 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_CRIT,4,90 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_ABSORB,4,40 },
	{ WT_WEAPON_2H,ST_RIGHT_HAND,IP_STUNCHANCE,4,250 }
};

static uint32_t GetPrototypeProperyValue(const std::vector<ItemProtValue>& list, eBalancePropery prop, uint32_t tier)
{
   auto it = std::find_if(list.begin(), list.end(), [prop, tier](auto check) {
      return check.prop == prop && check.tier == tier;
   });

   assert(it != list.end());

   return it->value;
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

   // Generate item type
   std::unordered_set<eItemType> types;
   std::vector<ItemProtValue> slotPrototypes;
   for(auto prot : ItemGenerator::Prototypes) {
      if(prot.slot == slot && prot.tier == item.tier) {
         slotPrototypes.push_back(prot);
      }
      types.insert(prot.type);
   }
   auto type_it = types.find(eItemType(std::uniform_int_distribution<int>(0, types.size() - 1)(random)));
   item.type = *type_it;

   // Generate random color
   int color_interval[] = { 0, 1, 2, 3, 4, 5, 6 };
   double color_weights[] = { 1, 2, 3, 4, 5, 6, 7 };
   std::piecewise_constant_distribution<> dist_color(std::begin(color_interval),
      std::end(color_interval),
      std::begin(color_weights));

   auto prefix_count = (int)dist_color(random);

   item.color = prefix_count;

   if(item.IsWeapon()) {
      item.params[eBalancePropery::IP_ATTACKPWMULTMAX] = std::uniform_int_distribution<int>(1, GetPrototypeProperyValue(slotPrototypes, eBalancePropery::IP_ATTACKPWMULTMAX, item.tier))(random);
   }

   if(item.IsShield()) {
      item.params[eBalancePropery::IP_BLOCKVAL] = std::uniform_int_distribution<int>(1, GetPrototypeProperyValue(slotPrototypes, eBalancePropery::IP_BLOCKVAL, item.tier))(random);
   }

   std::vector<eBalancePropery> addProperties;

   if(prefix_count > 0) {
      switch(item.type) {
/*
      case WT_WEAPON_RIFLE: {
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
         if(prefix_count > 6) addProperties.push_back(IP_STUNCHANCE);
         break;
      }
/*
      case WT_WEAPON_1H: {
         addProperties = { IP_ELEMDAMAGE_PYRE,
            IP_ELEMDAMAGE_FIRE,
            IP_ELEMDAMAGE_COLD,
            IP_ELEMDAMAGE_LIGHTNING,
            IP_ELEMDAMAGE_ACID,
            IP_ELEMDAMAGE_LIGHT,
            IP_ELEMDAMAGE_DARKNESS, IP_ATTACKPWR, IP_ATTACKPERTURN, IP_CRIT, IP_ABSORB };
         if(prefix_count > 6) addProperties.push_back(IP_BLEEDCHANCE);
         break;
      }*/
/*
      case WT_SHIELD: {
         addProperties = { ... };
         if(prefix_count > 6) addProperties.push_back(IP_BLOCKCHANCE);
         break;
      }
 */
      }
   }

   for(int i = 0; i < prefix_count; i++) {
      eBalancePropery add_property = *select_randomly(addProperties.begin(), addProperties.end(), random);
      auto val = std::uniform_int_distribution<int>(1, GetPrototypeProperyValue(slotPrototypes, add_property, item.tier))(random);
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

